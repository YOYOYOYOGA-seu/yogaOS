/*
 * @Author Shi Zhangkun
 * @Date 2020-06-27 04:11:02
 * @LastEditTime 2020-11-15 08:32:36
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/req.c
 */ 
#include "yogaOS/req.h"
#include "yogaOS/types.h"
#include "errno.h"

extern int enterSystemCall(int vector,int arg_1, int arg_2, int arg_3);

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t reqs(request_t * req, pid_t dest)
{
  return reqs_for(req,dest,0xFFFFFFFF);
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t reqs_for(request_t * req, pid_t dest, uint32_t wait)
{
  enterSystemCall(SYS_REQUEST,dest << 8,(int)req, wait);
  return enterSystemCall(SYS_REQUEST,1,(int)req, 0);
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t reqw(request_t * req)
{
  return reqw_for(req, 0xFFFFFFFF);
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t reqw_for(request_t * req, uint32_t wait)
{
  if(enterSystemCall(SYS_REQUEST,2,(int)req, wait) == ENOERR)
    return ENOERR;
  return enterSystemCall(SYS_REQUEST,2,(int)req, 0);
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t reqw_it(request_t * req)
{
  return reqw_it_for(req, 0xFFFFFFFF);
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t reqw_it_for(request_t * req, uint32_t wait)
{
  int ret = 1;
  if(enterSystemCall(SYS_REQUEST,3,(int)req, wait) == ENOERR)
    return ENOERR;
  return enterSystemCall(SYS_REQUEST,3,(int)req, 0); //req_wait_it
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t reqa(request_t * req)
{
  return enterSystemCall(SYS_REQUEST,4,(int)req, 0);
}