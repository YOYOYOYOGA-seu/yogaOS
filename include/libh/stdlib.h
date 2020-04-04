/*
 * @Author Shi Zhangkun
 * @Date 2020-04-03 23:47:05
 * @LastEditTime 2020-04-04 02:22:53
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/stdlib.h
 */
#ifndef __STDLIB_H
#define __STDLIB_H

double atof(char *str);
int atoi(char *str);
long atol(char *str);
char* itoa(int num,char* str,int radix);

#endif