/*
 * @Author Shi Zhangkun
 * @Date 2020-02-24 22:21:50
 * @LastEditTime 2020-03-08 07:19:14
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/sched/task.c
 */
#include "type.h"
#include "sched.h"
#include "errno.h"
#include "mm_page.h"
extern pid_t systemMaxPID;
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t task_initPCB(PCB_t *pPCB,uint32_t prio, const char* name,void (*taskFunc)(void), pageList_t temp)
{
  uint32_t i;
  pPCB->stateListItem.pOwner = pPCB;
  pPCB->eventListItem.pOwner = pPCB;
  pPCB->usingPageList.numberOfItem = 1;  //the PCB localed page itself
  pPCB->usingPageList.pFirstItem = temp.pFirstItem;
  
  pPCB->status = TASK_READY;
  pPCB->L1PageTbl = mm_allocOnePage(&pPCB->usingPageList);
    if(prio < SCHED_MAX_PRIO_NUM)
    pPCB->prio = prio;
  else
    pPCB->prio = SCHED_MAX_PRIO_NUM;

  pPCB->pid = sched_registerPID();
  pPCB->pidStatic = pPCB->pid;
  pPCB->totalTimeSlice = TASK_DEFUALT_TIME_SLICE;
  pPCB->timeLeft = TASK_DEFUALT_TIME_SLICE;
  pPCB->pStack = mm_allocOnePage(&pPCB->usingPageList);
  
  
  
  for(i = 0; (i < SCHED_MAX_TASK_NAME_SIZE && name[i] != '\0'); i++)
    pPCB->name[i] = name[i];
  pPCB->name[i] = '\0';
  task_initPCBArchRelevant(pPCB,taskFunc);
}

/**
 * @brief  Create a new task (with out father task)
 * @note   it would be use only in test system task
 * @param {void(*)(void)} taskFunc : point to the task function
 *        {uint32_t} codeSize 
 *        {uint32_t} prio
 *        {const char *} name
 * @retval error_t 
 */

error_t task_creatNewSysTask(void (*taskFunc)(void), uint32_t codeSize, uint32_t prio, const char* name)
{
  
  if(taskFunc == NULL || prio >= SCHED_MAX_PRIO_NUM )
    return ENOMEM;
  uint32_t needPageNum = TASK_INIT_NEED_PAGE_NUM;
  if(systemMaxPID != 0) 
  {

  }
  PCB_t * pNewPCB;
  pageList_t temp = {0,NULL};
  if(mm_checkIdleMemNum(systemMaxPID) == ENOSPC)
    return ENOSPC;
  pNewPCB = mm_allocOnePage(&temp);
  task_initPCB(pNewPCB, prio, name, taskFunc,temp);
  task_initTaskPage(pNewPCB);
  sched_addToList(pNewPCB);
}