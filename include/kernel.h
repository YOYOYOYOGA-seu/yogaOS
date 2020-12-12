/*
 * @Author Shi Zhangkun
 * @Date 2020-02-28 02:16:41
 * @LastEditTime 2020-12-03 16:54:48
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/kernel.h
 */
#ifndef __KERNEL_H
#define __KERNEL_H

#include "yogaOS/types.h"
#define assertk(a)  if(a){printk("/033[0;31;44m Assertion failed! file:%s, func:%s,line=%d\n\r",__FILE__, __func__, __LINE__);panic("assrt\n\r");}
volatile void panic(const char * errStr);
int printk(const char *format,...);
void* kmalloc(size_t size);
void* fmalloc(size_t size);
void kfree(void* ptr);
void ffree(void* ptr);
#endif
