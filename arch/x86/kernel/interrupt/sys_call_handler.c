/*
 * @Author Shi Zhangkun
 * @Date 2020-03-07 22:35:04
 * @LastEditTime 2020-03-21 21:37:43
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