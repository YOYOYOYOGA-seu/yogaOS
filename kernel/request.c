/*
 * @Author Shi Zhangkun
 * @Date 2020-04-18 21:27:25
 * @LastEditTime 2020-06-27 07:56:41
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/request.c
 */
#include "string.h"
#include "errno.h"
#include "request.h"
#include "sched.h"
#include "stdlib.h"
#include "req.h"


extern int enterSystemCall(int vector,int arg_1, int arg_2, int arg_3);



void req_init(request_t* req, pid_t pid)
{
  req->ownerPid = pid;
  req->type = 0;
  req->length = 0;
  req->pMesg = NULL; 
}


error_t req_anwser(request_t* req)
{
  
  
  PCB_t* pPCB = sched_serchTask(req->ownerPid,NULL);

  if(pPCB == NULL)
    return E_REQ_NO_USER;


  //copy result when the result is short (just using the buf in request struct rather than shared mem)
  pPCB->request.type = req->type;
  pPCB->request.length = req->length;
  pPCB->request.pMesg = req->pMesg;

  removeFromStateList(pPCB);
  pPCB->status = TASK_READY;
  sched_addToList(pPCB);
    
  return ENOERR;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t req_wait(request_t* req)
{
  request_t* pReqS;   //point to the next waiting task's PCB
  

  // the list should be ranged by prio, so the first item are always the highest prio to handler
  if(pLocalPCB->reqWaitList.numberOfItem >= 1)   
  {
    pLocalPCB->reqState = REQ_BUSY;
    pReqS = &((PCB_t *)pLocalPCB->reqWaitList.pFirstItem->pOwner)->request;

    req->type = pReqS->type;
    req->length = pReqS->length;
    req->pMesg = pReqS->pMesg;
    req->ownerPid = pReqS->ownerPid;

    list_removeformList(pLocalPCB->reqWaitList.pFirstItem);  //remove from waiting list
    
  }
  else  //no request in waiting list
  {   
    pLocalPCB->reqState = REQ_READY;
    sched_suspendTask(NULL, 0xFFFFFFFF);  //suspend task
    return E_REQ_NO_USER;
  }
  
  return ENOERR;  /* return the request in user virtual address area (can visit in user mode) */
  
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t req_result(request_t* req)
{
  req->type = pLocalPCB->request.type;
  req->length = pLocalPCB->request.length;
  req->pMesg = pLocalPCB->request.pMesg;

  return ENOERR;
}

/**
 * @brief  
 * @note  
 * @param {request_t*} pReqS : request struct be sent
 * @param {pid_t} servPid : destination server pid
 * @retval none
 */
error_t req_send(request_t* pReqS, pid_t servPid)
{
  if (0/* check if pMesg in the shared mem area  */)
  {
    /* code */
  }

  PCB_t* pPCB_R = sched_serchTask(servPid,NULL); //server task's PCB
  if(pPCB_R == NULL)
    return E_REQ_NO_SERV;


  pLocalPCB->request.type = pReqS->type;
  pLocalPCB->request.length = pReqS->length;
  pLocalPCB->request.pMesg = pReqS->pMesg;
  
  switch (pPCB_R->reqState)
  {
  
  case REQ_READY:  /* server task is idle, write to it's recive request struct directly */
    pPCB_R->reqState = REQ_BUSY;
    /* wake server task */
    break;

  case REQ_BUSY: /* server task is idle, write to user task's PCB, only add to wait list */
    //write request content to it's own request struct(for server task copy)
    break;
  default:
    return E_REQ_IVD;
    break;
  }

  pLocalPCB->eventListItem.value = pLocalPCB->p_prio; //value = prio, ranged by prio
    list_insertList(&pPCB_R->reqWaitList ,&(sched_serchTask(pLocalPCB->pid,NULL))->eventListItem);
  
  if(pPCB_R->status != TASK_READY)   //wake server task
  {
    removeFromStateList(pPCB_R);
    pPCB_R->status = TASK_READY;
    sched_addToList(pPCB_R);
  }
  sched_suspendTask(NULL, 0xFFFFFFFF);
  return ENOERR;
}

/**
 * @brief  
 * @note  
 * @param {request_t*} pReqS : request struct, the only useful msg is pReqS.ownerPid(used for serch the task be transponded)
 * @param {pid_t} servPid : destination server pid
 * @retval none
 */
error_t req_transpond(request_t* pReqS, pid_t servPid)
{
  PCB_t * pPCB_S = sched_serchTask(pReqS->ownerPid,NULL);
  if(pPCB_S == NULL)
    return E_REQ_NO_USER;

  
  PCB_t * pPCB_R = sched_serchTask(servPid,NULL);
  if(pPCB_R == NULL)
    return E_REQ_NO_SERV;
 

  switch (pPCB_R->reqState)
  {
  
  case REQ_READY:  /* server task is idle, write to it's recive request struct directly */
    pPCB_R->reqState = REQ_BUSY;
    /* wake server task */
    break;

  case REQ_BUSY: /* server task is idle, write to user task's PCB, only add to wait list */
    
    
    //write request content to it's own request struct(for server task copy)
    break;

  default:
    return E_REQ_IVD;
    break;
  }
    pPCB_S->eventListItem.value = pLocalPCB->p_prio; //value = prio, ranged by prio
    list_removeformList(&pLocalPCB->eventListItem);
    list_insertList(&pPCB_R->reqWaitList ,&pLocalPCB->eventListItem);
  if(pPCB_R->status != TASK_READY)   //wake server task
  {
    removeFromStateList(pPCB_R);
    pPCB_R->status = TASK_READY;
    sched_addToList(pPCB_R);
  }

  return ENOERR;
}