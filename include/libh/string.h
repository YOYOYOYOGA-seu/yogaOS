/*
 * @Author Shi Zhangkun
 * @Date 2020-02-25 02:50:21
 * @LastEditTime 2020-12-30 00:16:32
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/string.h
 */
#ifndef __STRING_H
#define __STRING_H
#include "yogaOS/types.h"

void * memcpy(void * dest, const void *src, int n);
void * memset(void *s, int ch, ssize_t n);
char *strcpy(char* dest, const char *src);
int strcmp(const char* str1, const char *str2);
int memcmp(const void *str1, const void *str2, size_t n);
#endif