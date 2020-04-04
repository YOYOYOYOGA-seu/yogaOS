/*
 * @Author Shi Zhangkun
 * @Date 2020-02-24 22:21:50
 * @LastEditTime 2020-04-04 08:36:39
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/sched/task.c
 */
#include "type.h"
#include "sched.h"
#include "errno.h"
#include "page.h"
#include "tty.h"
extern pid_t systemMaxPID;
extern tty_t * pCurrentActiveTTY;
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t task_initPCB(PCB_t *pPCB,uint32_t p_prio,uint32_t t_prio ,const char* name,void (*taskFunc)(void), pageList_t temp)
{
  uint32_t i;
  pPCB->stateListItem.pOwner = pPCB;
  pPCB->eventListItem.pOwner = pPCB;
  pPCB->usingPageList.numberOfItem = 1;  //the PCB localed page itself
  pPCB->usingPageList.pFirstItem = temp.pFirstItem;
  
  pPCB->status = TASK_READY;
  pPCB->L1PageTbl = page_allocOne(&pPCB->usingPageList);
    if(p_prio < SCHED_MAX_P_PRIO_NUM) //p_prio
    pPCB->p_prio = p_prio;
  else
    pPCB->p_prio = SCHED_MAX_P_PRIO_NUM;

    if(t_prio < SCHED_MAX_T_PRIO_NUM) //t_prio
    pPCB->t_prio = t_prio;
  else
    pPCB->t_prio = SCHED_MAX_T_PRIO_NUM;

  pPCB->pid = sched_registerPID();
  pPCB->pidStatic = pPCB->pid;
  pPCB->totalTimeSlice = TASK_MAX_TIME_SLICE - t_prio;
  pPCB->timeLeft = pPCB->totalTimeSlice;
  pPCB->pStackPage = page_allocOne(&pPCB->usingPageList);
  pPCB->retFuncPage = page_allocOne(&pPCB->usingPageList);
  
  (pCurrentActiveTTY == NULL )? (pPCB->tty = 0):(pPCB->tty = (int)pCurrentActiveTTY->ttyIndex);
  for(i = 0; (i < SCHED_MAX_TASK_NAME_SIZE && name[i] != '\0'); i++)
    pPCB->name[i] = name[i];
  pPCB->name[i] = '\0';
  task_initPCBArchRelevant(pPCB,taskFunc);
}

/**
 * @brief  Create a new task (with out father task)
 * @note   it would be use only in test system task
 * @param {void(*)(void)} taskFunc : point to the task function
 * @param {uint32_t} codeSize 
 * @param {uint32_t} p_prio
 * @param {const char *} name
 * @retval error_t 
 */

error_t task_creatNewSysTask(void (*taskFunc)(void), uint32_t codeSize, uint32_t p_prio,uint32_t t_prio , const char* name)
{
  
  if(taskFunc == NULL || p_prio >= SCHED_MAX_P_PRIO_NUM )
    return ENOMEM;
  uint32_t needPageNum = TASK_INIT_NEED_PAGE_NUM;
  if(systemMaxPID != 0) 
  {

  }
  PCB_t * pNewPCB;
  pageList_t temp = {0,NULL};
  if(page_checkIdleMemNum(systemMaxPID) == ENOSPC)
    return ENOSPC;
  pNewPCB = page_allocOne(&temp);
  task_initPCB(pNewPCB, p_prio, t_prio , name, taskFunc,temp);
  task_initTaskPage(pNewPCB);
  sched_addToList(pNewPCB);
}