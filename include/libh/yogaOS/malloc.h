/*
 * @Author Shi Zhangkun
 * @Date 2020-09-12 02:53:06
 * @LastEditTime 2022-05-06 21:51:10
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/include/libh/yogaOS/malloc.h
 */
#ifndef __MALLOC_H
#define __MALLOC_H

#include "yogaOS/types.h"
/* define -------------------------------------------------*/
#define AIGN_SIZE sizeof(void*)  //must be the mutiply of sizeof(void*)
#define MALLOC_USE_MEM_SIZE (4096*4096)     //only use the beginning 16M area of task heap linear addr area for malloc use
/* typedef -------------------------------------------------*/
typedef struct memBlock{
  struct memBlock *pNext;
  size_t size;
}memBlock_t;

typedef struct{
  memBlock_t *pIdeMapBase;
  memBlock_t *pUsingMapBase;
  size_t ideSize;
  size_t usingSize;
  void *pBase;
  void *pTop;
  uint32_t usingBlockNum;
  uint32_t ideBlockNum;
}memArea_t;

void * mem_getHeapLocation(void);
#endif