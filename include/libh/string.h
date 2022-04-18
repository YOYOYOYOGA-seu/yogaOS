/*
 * @Author Shi Zhangkun
 * @Date 2020-02-25 02:50:21
 * @LastEditTime 2022-04-18 16:15:58
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/include/libh/string.h
 */
#ifndef __STRING_H
#define __STRING_H
#include "yogaOS/types.h"

void * memcpy(void * dest, const void *src, int n);
void * memset(void *s, int ch, ssize_t n);
char *strcpy(char* dest, const char *src);
int strcmp(const char* str1, const char *str2);
int memcmp(const void *str1, const void *str2, size_t n);
size_t strlen(const char *str);
#endif