/*
 * @Author Shi Zhangkun
 * @Date 2020-03-09 02:17:29
 * @LastEditTime 2020-09-12 00:11:00
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/process.c
 */

#include "unistd.h"

extern int enterSystemCall(int vector,int arg_1, int arg_2, int arg_3);

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
pid_t fork(void)
{
  pid_t pid;
  pid = enterSystemCall(SYS_FORK_VECTOR, 0, 0, 0);
  if(pid == enterSystemCall(SYS_GET_PID_VECTOR, 0, 0, 0))
    return 0;
  else
    return pid;
  
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
volatile void exit(int __status)
{
  enterSystemCall(SYS_EXIT_VECTOR, __status, 0, 0);

}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
unsigned sleep(unsigned int __seconds)
{
  unsigned int __microsecond;
  if(__seconds == 0xFFFFFFFF)  //0xFFFFFFFF respect suspend  always
    __microsecond = 0xFFFFFFFF;   
  else if(__seconds >= 0xFFFFFFFF/1000)
    __microsecond = 0xFFFFFFFE;    //max delay time 
  else
    __microsecond = 1000*__seconds;
  
  return (unsigned)enterSystemCall(SYS_SLEEP_VECTOR, __microsecond, 0, 0);
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
unsigned msleep(unsigned int __microsecond)
{
  return (unsigned)enterSystemCall(SYS_SLEEP_VECTOR, __microsecond, 0, 0);
}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
pid_t getpid(void)
{
  return (pid_t)enterSystemCall(SYS_GET_PID_VECTOR, 0, 0, 0);
}