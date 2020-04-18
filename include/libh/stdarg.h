/*
 * @Author Shi Zhangkun
 * @Date 2020-04-03 23:33:09
 * @LastEditTime 2020-04-18 02:29:43
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/stdarg.h
 */
#ifndef __STDARG_H
#define __STDARG_H

typedef char* va_list;

#define _INTSIZEOF(n) ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define va_start(ap,v) ( ap = (va_list)&v + _INTSIZEOF(v) )
#define va_arg(ap,t) ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap) ( ap = (va_list)0 )


#endif
