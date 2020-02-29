/*
 * @Author Shi Zhangkun
 * @Date 2020-02-25 00:19:41
 * @LastEditTime 2020-02-29 03:18:35
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/sched/sched.c
 */
#include "type.h"
#include "sched.h"
#include "errno.h"
#include "mm_page.h"
#include "kernel.h"

PCB_t * currentActiveTask = NULL; 
uint32_t taskLeftTime;
uint32_t schedRunningTime; 
list_t  readyTaskList[SCHED_MAX_PRIO_NUM];  //Ready task list
list_t  hungUpTaskList[SCHED_MAX_PRIO_NUM];

uint32_t volatile topReadyPriority = SCHED_MAX_PRIO_NUM; //save the highest task prio in ready list
shcedulerState_t shcedulerState = SCHEDULER_STOP; //scheduler state
pid_t systemMaxPID = 0; //record the pid have been alloced(now don't recycle pit)

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void inline shced_switchToNextReadyPrio(void)
{
  uint32_t i;
  for(i = topReadyPriority; i < SCHED_MAX_PRIO_NUM; i++)
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
error_t sched_addToList(PCB_t *pPCB, taskState_t state)
{
  switch (state)
  {
  case TASK_READY:
    list_insertList(&readyTaskList[pPCB->prio], &(pPCB->stateListItem));
    break;
  case TASK_PENDING:
    list_insertList(&readyTaskList[pPCB->prio], &(pPCB->stateListItem));
    break;
  default:
    return E_SCHED_NOT_SPT_STATE;
    break;
  }
  if(pPCB->prio < topReadyPriority)  //update the highest ready priority
    topReadyPriority = pPCB->prio;
  return ENOERR;
}
error_t removeFromList(PCB_t *pPCB)
{

}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t sched_initScheduler(void)
{
  uint32_t i;
  taskLeftTime = 0;
  for(i = 0; i < SCHED_MAX_PRIO_NUM; i++)
  {
    list_initList(&readyTaskList[i], TASK_READY_LIST_MAX_VALUE);
    list_initList(&hungUpTaskList[i], TASK_HUNG_UP_LIST_MAX_VALUE);
  }
  
}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void sched_startScheduler(void)
{
  shcedulerState = SCHEDULER_RUN;
  currentActiveTask = readyTaskList[topReadyPriority].pFirstItem->pOwner;
  taskLeftTime = currentActiveTask->totalTimeSlice;
  sched_loadFirstTask(currentActiveTask);

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
    return;
  if(taskLeftTime > 0)
    taskLeftTime--;
  schedRunningTime ++;
  
}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
uint32_t sched(void)
{
  if(shcedulerState != SCHEDULER_RUN)
    return;

  uint32_t flag;
  if(taskLeftTime == 0)
  {
    currentActiveTask->timeLeft = currentActiveTask->totalTimeSlice;
    readyTaskList[currentActiveTask->prio].pFirstItem = currentActiveTask->stateListItem.pNext;
    currentActiveTask = readyTaskList[currentActiveTask->prio].pFirstItem->pOwner;
    taskLeftTime = currentActiveTask->timeLeft;
    flag = 1;
  }
  if(topReadyPriority < currentActiveTask->prio)
  {
    currentActiveTask->timeLeft = taskLeftTime; //save current task left time slice
    if(readyTaskList[topReadyPriority].numberOfItem == 0)
      painc("No task in this prio!\n");
    currentActiveTask = readyTaskList[topReadyPriority].pFirstItem->pOwner;
    taskLeftTime = currentActiveTask->timeLeft;
    flag = 1;
  }
  if(flag == 1) //need sched
  {
    return currentActiveTask->L1PageTbl;
  }
  return (uint32_t)NULL;
}


