/*
 * @Author Shi Zhangkun
 * @Date 2020-09-12 05:05:52
 * @LastEditTime 2020-09-12 07:38:46
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/mm/heap.c
 */

#include "yogaOS/malloc.h"
#include "mm.h"

/**
 * @brief  init the malloc manager struct
 * @note   the malloc using memory area are in the beginning of heap, and be inited whe the task created
 * @param {type} none
 * @retval none
 */
void heap_initMalloc(void)
{
  
  memArea_t* memArea = mem_getHeapLocation();  //the struct located in the start of heap
  void *base = (void *)memArea + ((sizeof(memArea_t)/AIGN_SIZE) + 1)*(AIGN_SIZE);  
  /*Mem Area struct init*/
  memArea->pIdeMapBase =(memBlock_t*)base;
  memArea->ideBlockNum = 1;
  memArea->ideSize =AIGN_SIZE * ((MALLOC_USE_MEM_SIZE - sizeof(memArea_t) - sizeof(memBlock_t))/AIGN_SIZE);

  memArea->pUsingMapBase = NULL;
  memArea->usingBlockNum = 0;
  memArea->usingSize = sizeof(memBlock_t);
  
  memArea->pBase = base;
  memArea->pTop = (void *)((char *)base + memArea->ideSize + sizeof(memBlock_t) - 1);

  /*first mem block init*/
  memArea->pIdeMapBase->pNext = NULL;
  memArea->pIdeMapBase->size = AIGN_SIZE * ((MALLOC_USE_MEM_SIZE - sizeof(memArea_t) - sizeof(memBlock_t))/AIGN_SIZE);
}
