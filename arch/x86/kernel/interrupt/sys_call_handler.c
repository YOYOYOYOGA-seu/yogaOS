/*
 * @Author Shi Zhangkun
 * @Date 2020-03-07 22:35:04
 * @LastEditTime 2020-04-04 07:16:43
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/kernel/interrupt/sys_call_handler.c
 */

#include "sys.h"
#include "time.h"
#include "sched.h"
#include "tty.h"

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
__attribute__((weak)) int sys_exit(void)
{
  
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
  return time_getTimeCount();
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