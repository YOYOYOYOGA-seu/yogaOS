/*
 * @Author Shi Zhangkun
 * @Date 2020-03-07 22:35:04
 * @LastEditTime 2020-03-09 05:48:15
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/kernel/interrupt/sys_call_handler.c
 */

#include "sys.h"
#include "time.h"
#include "sched.h"


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
 * @param {int} s :unit second
 * @retval none
 */
__attribute__((weak)) int sys_sleep(int s)
{
  sched_suspendTask(NULL, s*1000/SYSTEM_TICK);
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