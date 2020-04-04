/*
 * @Author Shi Zhangkun
 * @Date 2020-04-03 23:27:33
 * @LastEditTime 2020-04-04 02:31:39
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/stdio.h
 */
#ifndef __STDIO_H
#define __STDIO_H

#include "stdarg.h"

int printf(const char *format,...);
int vsprintf(char *string, char *format, va_list param);
int sprintf(char *string, const char *format,...);
#endif