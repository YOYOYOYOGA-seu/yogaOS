/*
 * @Author Shi Zhangkun
 * @Date 2020-04-03 23:47:05
 * @LastEditTime 2020-09-12 06:33:51
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/stdlib.h
 */
#ifndef __STDLIB_H
#define __STDLIB_H

#include "yogaOS/types.h"

double atof(char *str);
int atoi(char *str);
long atol(char *str);
char* itoa(int num,char* str,int radix);
void free(void *ptr);
void* malloc(size_t size);
int rand(void);
void srand(unsigned int seed);
#endif