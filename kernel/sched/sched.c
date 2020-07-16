/*
 * @Author Shi Zhangkun
 * @Date 2020-02-25 00:19:41
 * @LastEditTime 2020-06-25 02:24:40
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/sched/sched.c
 */
#include "yogaOS/types.h"
#include "sched.h"
#include "errno.h"
#include "page.h"
#include "kernel.h"
#include "time.h"
#include "string.h"
PCB_t * currentActiveTask = NULL; 
static uint32_t taskLeftTime;
static uint32_t schedRunningTime = 0; 
static uint32_t nextTaskwakeTime = 0;
static list_t  readyTaskList[SCHED_MAX_P_PRIO_NUM];  //Ready task list
static list_t  suspendTaskList;

static uint32_t volatile topReadyPriority = SCHED_MAX_P_PRIO_NUM; //save the highest task p_prio in ready list
static shcedulerState_t shcedulerState = SCHEDULER_STOP; //scheduler status
static PCB_t* globalTaskMap[SCHED_MAX_TASK_NUM];
pid_t sysFirstIdlePID = 0; //record the pid have been alloced(now don't recycle pit)
static int taskNumber = 0;
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void sched_switchToNextReadyPrio(void)
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

void sched_changeState(shcedulerState_t state)
{
  shcedulerState = state;
}
/**
 * @brief  serch a task in global task map, can choose if use task name for check
 * @note  
 * @param {pid_t} pid:
 * @param {const char*} name_chk: task name for check, use NULL if don't need check 
 * @retval PCB_t*
 */
PCB_t* sched_serchTask(pid_t pid, const char* name_chk)
{
  if(pid >= SCHED_MAX_TASK_NUM)
    return NULL;
  if(name_chk == NULL)
  {
    return globalTaskMap[pid];
  }
  else if(globalTaskMap[pid] != NULL)
  {
    if(!strcmp((const char*)globalTaskMap[pid]->name,name_chk))
      return globalTaskMap[pid];
  }
  return NULL;
}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
pid_t sched_serchNextIdlePID(void)
{
  int i;
  for(i = 0; i < SCHED_MAX_TASK_NUM; i++)
  {
    if(globalTaskMap[i] == NULL)
      return (pid_t)i;
  }
  return SCHED_MAX_TASK_NUM;
  
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
pid_t sched_registerPID(PCB_t * pPCB)
{
  if(sysFirstIdlePID >= SCHED_MAX_TASK_NUM)
    painc("sched:out max task number limit!!!!\n\r");  //should not run to this (before register must check running task quantity)
  pid_t temp = sysFirstIdlePID;
  globalTaskMap[sysFirstIdlePID] = pPCB;
  sysFirstIdlePID = sched_serchNextIdlePID();
  taskNumber ++;
  return temp;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void sched_logoutPID(pid_t pid)
{
  globalTaskMap[pid] = NULL;
  if(pid < sysFirstIdlePID )
    sysFirstIdlePID = pid;
  taskNumber --;
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
   sched_switchToNextReadyPrio();
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
  memset(globalTaskMap,0,sizeof(globalTaskMap));
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
 * @note  warning !!!!!!!! not to wake some specific task but a period wake action
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
error_t sched_deleteTask(pid_t pid)
{
  if(pid >= SCHED_MAX_TASK_NUM)
    return E_SCHED_OUT_TSK_NR;
  PCB_t *pPCB = globalTaskMap[pid];
  

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


