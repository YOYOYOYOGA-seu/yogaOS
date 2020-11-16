/*
 * @Author Shi Zhangkun
 * @Date 2020-04-18 21:27:40
 * @LastEditTime 2020-11-15 04:50:59
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/request.h
 */
#ifndef __REQUEST_H
#define __REQUEST_H
#include "yogaOS/types.h"
#include "yogaOS/list.h"
#include "yogaOS/req.h"
#define REQ_MAX_WAIT_TASK 0xFFFFFFFF   // max quantity of tasks waiting in the same time

typedef enum{
  REQ_WAIT,
  REQ_WAIT_IT,
  REQ_BUSY,
  REQ_INVALID,      //can't receive request
}reqState_t;




/* ----------------------- function declaration ------------------------------------ */
void req_init(request_t* req, pid_t pid);
void req_init_it(request_t* req);

error_t req_wait(request_t* req, uint32_t wait);
error_t req_wait_it(request_t* req, uint32_t wait);
error_t req_anwser(request_t* req);

error_t req_send(request_t* pReqS, pid_t servPid, uint32_t wait);
error_t req_send_it(request_t* pReqS, pid_t servPid);
error_t req_result(request_t* req);

error_t req_transpond(request_t* pReqS, pid_t servPid);
#endif