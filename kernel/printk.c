/*
 * @Author Shi Zhangkun
 * @Date 2020-04-05 05:06:33
 * @LastEditTime 2020-10-25 05:26:22
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/printk.c
 */
#include "kernel.h"
#include "stdarg.h"
#include "stdio.h"
#include "tty.h"
/**
 * @brief  print format string to tty
 * @note    used by kernel and kernel server process
 * @param {const char *} format : format string
 * @param {...} ... : format param
 * @retval none
 */
extern tty_t* pCurrentActiveTTY;
int printk(const char *format,...)
{
  int i;
  va_list arg = (va_list)((char *)&format + 4);
  char buf[256];

  i = vsprintf(buf, (char *)format, arg);
  if(pCurrentActiveTTY != NULL)
    tty_write(pCurrentActiveTTY->ttyIndex,buf,i);  /* 需要注意，无论是内核还是系统服务进程，其都是没有对应的tty的，应该设法打印到当前活动的tty */
                                                    
    tty_outputData(pCurrentActiveTTY->ttyIndex);
  return i;

}