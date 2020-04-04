/*
 * @Author Shi Zhangkun
 * @Date 2020-02-25 00:19:41
 * @LastEditTime 2020-04-04 08:36:24
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/sched/sched.c
 */
#include "type.h"
#include "sched.h"
#include "errno.h"
#include "page.h"
#include "kernel.h"
#include "time.h"
PCB_t * currentActiveTask = NULL; 
uint32_t taskLeftTime;
uint32_t schedRunningTime = 0; 
uint32_t nextTaskwakeTime = 0;
list_t  readyTaskList[SCHED_MAX_P_PRIO_NUM];  //Ready task list
list_t  suspendTaskList;

uint32_t volatile topReadyPriority = SCHED_MAX_P_PRIO_NUM; //save the highest task p_prio in ready list
shcedulerState_t shcedulerState = SCHEDULER_STOP; //scheduler status
pid_t systemMaxPID = 0; //record the pid have been alloced(now don't recycle pit)

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void shced_switchToNextReadyPrio(void)
{
  uint32_t i;
  for(i = topReadyPriority; i < SCHED_MAX_P_PRIO_NUM; i++)
  {
    if(readyTaskList[i].numberOfItem > 0)
    {
      topReadyPriority = i;
      return;
    }
  }
  painc("No task in ready list!\n\0");
}



/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
pid_t sched_registerPID(void)
{
  systemMaxPID ++;
  return systemMaxPID - 1;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
pid_t sched_getCurrentPID(void)
{
  if(currentActiveTask != NULL)
    return currentActiveTask->pid;
  else
    return 0;
  
}
/**
 * @brief  add a PCB to a task list according to it's status
 * @note  
 * @param {PCB_t *} pPCB
 * @retval error_t
 */
error_t sched_addToList(PCB_t *pPCB)
{
  switch (pPCB->status)
  {
  case TASK_READY:
    list_insertTail(&readyTaskList[pPCB->p_prio], &(pPCB->stateListItem));
    if(pPCB->p_prio < topReadyPriority)  //update the highest ready priority
    topReadyPriority = pPCB->p_prio;
    break;
  case TASK_SUSPENDING:
    list_insertList(&suspendTaskList, &(pPCB->stateListItem));
    break;
  default:
    return E_SCHED_NOT_SPT_STATE;
    break;
  }
  
  return ENOERR;
}

/**
 * @brief  Remove a PCB from it's task list
 * @note  
 * @param {PCB_t *} pPCB
 * @retval error_t
 */
error_t removeFromStateList(PCB_t *pPCB)
{
  int flag = 0;
  error_t errno;
  if(pPCB->status <= TASK_READY )
    flag = 1;
  errno = list_removeformList(&pPCB->stateListItem);
  if(errno != ENOERR)
    return errno;
  
  if (flag && pPCB->p_prio <= topReadyPriority)  // if this is a task in ready list ,we should check topReadyPrio
  {
   shced_switchToNextReadyPrio();
  }
  
  return ENOERR;

  
}
/**
 * @brief  init scheduler
 * @note  
 * @param {type} none
 * @retval none
 */
error_t sched_initScheduler(void)
{
  uint32_t i;
  taskLeftTime = 0;
  for(i = 0; i < SCHED_MAX_P_PRIO_NUM; i++)
  {
    list_initList(&readyTaskList[i], TASK_READY_LIST_MAX_VALUE);
    
  }
  list_initList(&suspendTaskList, TASK_SUSP_LIST_MAX_VALUE);
}

/**
 * @brief  start schedule
 * @note  
 * @param {type} none
 * @retval none
 */
void sched_startScheduler(void)
{
  shcedulerState = SCHEDULER_RUN;
  currentActiveTask = readyTaskList[topReadyPriority].pFirstItem->pOwner;
  currentActiveTask->status = TASK_RUN;
  taskLeftTime = currentActiveTask->totalTimeSlice;
  sched_loadFirstTask(currentActiveTask);

}

/**
 * @brief  Suspend a task for a certain time
 * @note  
 * @param {PCB_t *} pPCB
 * @param {uint32_t} time
 * @retval error_t
 */
error_t sched_suspendTask(PCB_t *pPCB, uint32_t time)
{
  if(pPCB == NULL)
    pPCB = currentActiveTask;
  if(shcedulerState != SCHEDULER_RUN)
    return E_SCHED_NOT_RUN;
  uint32_t wakeTime;
  if(TASK_SUSP_LIST_MAX_VALUE - schedRunningTime >= time)
    wakeTime = time + schedRunningTime;
  else
    wakeTime = TASK_SUSP_LIST_MAX_VALUE;
  
  if(pPCB->status > TASK_READY)
    return E_SUSPEND;
  removeFromStateList(pPCB);
  pPCB->status = TASK_SUSPENDING;
  pPCB->stateListItem.value = wakeTime;
  sched_addToList(pPCB);
  //update the next wake up task time
  nextTaskwakeTime = suspendTaskList.pFirstItem->value;
  
}

/**
 * @brief  wake task which suspend time is over
 * @note  
 * @param {PCB_t *} pPCB
 * @param {uint32_t} time
 * @retval error_t
 */
error_t sched_wakeTask(void)
{
  if(shcedulerState != SCHEDULER_RUN)
    return E_SCHED_NOT_RUN;

  int i, num;
  PCB_t * pPCB;
  num = suspendTaskList.numberOfItem;
  for(i = 0; i < num; i++)
  {
    if(suspendTaskList.pFirstItem->value <= schedRunningTime)
    {
      pPCB = suspendTaskList.pFirstItem->pOwner;
      removeFromStateList(pPCB);
      pPCB->status = TASK_READY;
      sched_addToList(pPCB);
    }
  }
  return ENOERR;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void sched_timeTick(void)
{
  if(shcedulerState != SCHEDULER_RUN)
    return ;
  if(taskLeftTime > 0)
    taskLeftTime--;
  schedRunningTime ++;
  if(nextTaskwakeTime <= schedRunningTime)
    sched_wakeTask();

}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval the L1 page table linear address
 */
uint32_t schedule(void)
{
  if(shcedulerState != SCHEDULER_RUN)
    return (uint32_t)NULL;

  uint32_t flag;
  if(taskLeftTime == 0 )
  {
    currentActiveTask->timeLeft = currentActiveTask->totalTimeSlice;
    if(currentActiveTask->status == TASK_RUN)  //if current task haven't be pending
      currentActiveTask->status = TASK_READY;

    if(readyTaskList[currentActiveTask->p_prio].numberOfItem != 0) // prevent the current p_prio have no task
    {
      readyTaskList[currentActiveTask->p_prio].pFirstItem =readyTaskList[currentActiveTask->p_prio].pFirstItem->pNext;
      currentActiveTask = readyTaskList[currentActiveTask->p_prio].pFirstItem->pOwner;
      currentActiveTask -> status = TASK_RUN;
    }
    else
    {
      if(topReadyPriority >= currentActiveTask->p_prio)
        painc("topReadyPriority error!\n");
    }
    //before check the if the are a higher p_prio,we suppose it is the task to run
    taskLeftTime = currentActiveTask->timeLeft; 
    flag = 1;
  }
  //relocate the task to run , if the are a higher p_prio task ready, or current task is pending
  if(topReadyPriority < currentActiveTask->p_prio || currentActiveTask->status != TASK_RUN)  
  {
    currentActiveTask->timeLeft = taskLeftTime; //save current task left time slice
    if(currentActiveTask->status == TASK_RUN)
      currentActiveTask->status = TASK_READY;
    if(readyTaskList[topReadyPriority].numberOfItem == 0)
      painc("No task in this preempting priority!\n");
    currentActiveTask = readyTaskList[topReadyPriority].pFirstItem->pOwner;
    currentActiveTask->status = TASK_RUN;
    taskLeftTime = currentActiveTask->timeLeft;
    flag = 1;
  }
  if(flag == 1) //need sched
  {
    return (uint32_t)currentActiveTask->L1PageTbl;
  }
  return (uint32_t)NULL;
}


