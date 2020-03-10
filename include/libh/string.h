/*
 * @Author Shi Zhangkun
 * @Date 2020-02-25 02:50:21
 * @LastEditTime 2020-02-26 01:37:58
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/string.h
 */
#ifndef __STRING_H
#define __STRING_H
#include "type.h"

void * memcpy(void * dest, const void *src, int n);

void * memset(void *s, int ch, size_t n);
#endif