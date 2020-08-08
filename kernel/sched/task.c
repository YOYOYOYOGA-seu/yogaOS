/*
 * @Author Shi Zhangkun
 * @Date 2020-02-24 22:21:50
 * @LastEditTime 2020-08-08 05:42:08
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/sched/task.c
 */
#include "yogaOS/types.h"
#include "sched.h"
#include "errno.h"
#include "page.h"
#include "tty.h"
extern pid_t sysFirstIdlePID;
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
  pPCB->usingPageList.value = 1;  //the PCB localed page itself
  pPCB->usingPageList.firstItem = temp.firstItem;
  
  pPCB->status = TASK_READY;
  pPCB->L1PageTbl = page_allocOne(&pPCB->usingPageList,IDLE_AREA);
    if(p_prio < SCHED_MAX_P_PRIO_NUM) //p_prio
    pPCB->p_prio = p_prio;
  else
    pPCB->p_prio = SCHED_MAX_P_PRIO_NUM;

    if(t_prio < SCHED_MAX_T_PRIO_NUM) //t_prio
    pPCB->t_prio = t_prio;
  else
    pPCB->t_prio = SCHED_MAX_T_PRIO_NUM;

  pPCB->pid = sched_registerPID(pPCB);
  pPCB->pidStatic = pPCB->pid;
  pPCB->totalTimeSlice = TASK_MAX_TIME_SLICE - t_prio;
  pPCB->timeLeft = pPCB->totalTimeSlice;
  pPCB->pStackPage = page_allocOne(&pPCB->usingPageList,IDLE_AREA);
  pPCB->retFuncPage = page_allocOne(&pPCB->usingPageList,IDLE_AREA);
  
  (pCurrentActiveTTY == NULL )? (pPCB->tty = 0):(pPCB->tty = (int)pCurrentActiveTTY->ttyIndex);
  for(i = 0; (i < SCHED_MAX_TASK_NAME_SIZE && name[i] != '\0'); i++)
    pPCB->name[i] = name[i];
  pPCB->name[i] = '\0';

  req_init(&pPCB->request, pPCB->pid); //deinit request struct
  list_initList(&pPCB->reqWaitList, REQ_MAX_WAIT_TASK);
  pPCB->reqState = REQ_INVALID;

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
  
  if(sysFirstIdlePID != 0) 
  {

  }
  if(sysFirstIdlePID >= SCHED_MAX_TASK_NUM)
    return E_SCHED_OUT_TSK_NR;
  if(page_checkIdleMemNum(needPageNum,IDLE_AREA) == ENOSPC)
    return ENOSPC;
  PCB_t * pNewPCB;
  pageList_t temp = {0,NULL};
  
  pNewPCB = page_allocOne(&temp,IDLE_AREA);
  task_initPCB(pNewPCB, p_prio, t_prio , name, taskFunc,temp);
  task_initTaskPage(pNewPCB);
  sched_addToList(pNewPCB);
}