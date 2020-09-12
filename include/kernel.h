/*
 * @Author Shi Zhangkun
 * @Date 2020-02-28 02:16:41
 * @LastEditTime 2020-09-12 00:29:46
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/kernel.h
 */
#ifndef __KERNEL_H
#define __KERNEL_H

#define assertk(a)  if(a){printk("/033[0;31;44m Assertion failed! file:%s, func:%s,line=%d\n\r",__FILE__, __func__, __LINE__);painc("assrt\n\r");}
volatile void painc(const char * errStr);
int printk(const char *format,...);
#endif
