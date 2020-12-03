/*
 * @Author Shi Zhangkun
 * @Date 2020-02-28 02:13:42
 * @LastEditTime 2020-06-27 04:46:15
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/panic.c
 */
#include "kernel.h"
/**
 * @brief  fuction
 * @note  
 * @param {type} none
 * @retval none
 */

volatile void panic(const char * errStr)
{
  printk("panic: %s",errStr);
  while(1)
  {

  }
}

