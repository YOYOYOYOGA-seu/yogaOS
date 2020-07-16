/*
 * @Author Shi Zhangkun
 * @Date 2020-06-27 04:11:02
 * @LastEditTime 2020-06-27 07:59:49
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/req.c
 */ 
#include "yogaOS/req.h"
#include "yogaOS/types.h"
#include "errno.h"

extern int enterSystemCall(int vector,int arg_1, int arg_2, int arg_3);

error_t reqs(request_t * req, pid_t dest)
{
  enterSystemCall(SYS_REQUEST,0,(int)req, dest);
}

error_t reqr(request_t * req)
{
  enterSystemCall(SYS_REQUEST,1,(int)req, 0);
}

unsigned int reqw(request_t * req)
{
  int ret = 1;
  while(ret != ENOERR)
  {
    ret = enterSystemCall(SYS_REQUEST,2,(int)req, 0) ;
  }
  return req->type;
}


error_t reqa(request_t * req)
{
  return enterSystemCall(SYS_REQUEST,3,(int)req, 0);
}