/*
 * @Author Shi Zhangkun
 * @Date 2020-04-03 23:02:17
 * @LastEditTime 2020-04-04 02:32:36
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/printf.c
 */
#include "stdio.h"
#include "stdarg.h"
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
int printf(const char *format,...)
{
  int i;
  va_list arg = (va_list)((char *)&format + 4);
  char buf[256];

  i = vsprintf(buf, (char *)format, arg);
  //write();
  return i;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
int sprintf(char *string, const char *format,...)
{
  int i;
  va_list arg = (va_list)((char *)&format + 4);

  i = vsprintf(string, (char *)format, arg);
  //write();
  return i;
}