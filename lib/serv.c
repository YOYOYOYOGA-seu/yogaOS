/*
 * @Author Shi Zhangkun
 * @Date 2022-04-18 15:59:40
 * @LastEditTime 2022-05-06 21:43:53
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/lib/serv.c
 */
#include "yogaOS/serv.h"

extern int enterSystemCall(int vector,int arg_1, int arg_2, int arg_3);

error_t serv_reg(char* name)
{
  return enterSystemCall(SYS_SERV_VECTOR, 0, (int)(name), 0);
}

error_t serv_remove(char* name)
{
  return enterSystemCall(SYS_SERV_VECTOR, 1, (int)(name), 0);
}

pid_t serv_search(char* name)
{
  return enterSystemCall(SYS_SERV_VECTOR, 2, (int)(name), 0);
}

void sfree(void *ptr)
{
  enterSystemCall(SYS_FREE_VECTOR, 0, (int)(ptr), 0);
}

void* smalloc(size_t size)
{
  return (void*)enterSystemCall(SYS_MALLOC_VECTOR, 0, size, 0);
}