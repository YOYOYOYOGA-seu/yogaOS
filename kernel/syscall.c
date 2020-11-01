/*
 * @Author Shi Zhangkun
 * @Date 2020-03-07 22:35:04
 * @LastEditTime 2020-11-01 08:19:46
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/syscall.c
 */

#include "sys.h"
#include "time.h"
#include "sched.h"
#include "tty.h"
#include "request.h"
#include "kernel.h"
#include "string.h"
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */

int sys_request(int mode, request_t * req, pid_t servPid)
{
  switch (mode)
  {
  case 0:    //send a request
    return req_send(req,servPid);
    break;
  case 1:    //get a request tesult
    return req_result(req);
    break;
  case 2:    //wait a request
    return req_wait(req);
    break;
  case 3:
    return req_anwser(req);
    break;
  case 4:
    return req_transpond(req,servPid);
    break;
  default:
    painc("iligal request system call mode !!!");
    return 0;
  }
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
__attribute__((weak)) int sys_exit(int status)
{
  sched_exit(status);
  return 0;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
__attribute__((weak)) int sys_fork(void)
{
  return 0;
}
/**
 * @brief  sleep system call handler
 * @note  
 * @param {int} ms :unit microsecond
 * @retval none
 */
__attribute__((weak)) int sys_sleep(int ms)
{
  if(ms == 0xFFFFFFFF) //always suspend 
    sched_suspendTask(NULL, 0xFFFFFFFF);
  else
    sched_suspendTask(NULL, ms/SYSTEM_TICK);
  return 0;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
__attribute__((weak)) int sys_wait(void)
{
  return 0;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
__attribute__((weak)) int sys_kill(void)
{
  return 0;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
__attribute__((weak)) int sys_excve(void)
{
  return 0;
}

/**
 * @brief  return the current running task pid
 * @note  
 * @param {type} none
 * @retval none
 */

__attribute__((weak)) int sys_getPID(void)
{
  return sched_getCurrentPID();
}

/**
 * @brief  return the time from system init
 * @note   unit ms
 * @param {type} none
 * @retval none
 */
__attribute__((weak)) int sys_getTime(void)
{
  unsigned int ut = time_getTimeCount();
  int t = 0;
  memcpy(t, ut, sizeof(int));
  return t;
}

/**
 * @brief  return the time from system init
 * @note   unit ms
 * @param {type} none
 * @retval none
 */
__attribute__((weak)) int sys_write(int ttyNum,void * buf,int count)
{
  int i;
  if(ttyNum < 0)
    ttyNum = currentActiveTask->tty;
  i = tty_write(ttyNum, buf, count);
  /* 注意！！！！！这是一个临时的系统调用，此时没有文件系统，只是做为tty写功能的实现，后期直接在FS中新定义（有weak修饰） */
  return i;
}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
__attribute__((weak)) int sys_read(void)
{
  return 0;
}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
__attribute__((weak)) int sys_open(void)
{
  return 0;
}