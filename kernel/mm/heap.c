/*
 * @Author Shi Zhangkun
 * @Date 2020-09-12 05:05:52
 * @LastEditTime 2022-05-07 16:56:36
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
void heap_initMalloc(void* firstPage, void* heapBase)
{
  memArea_t* memArea = firstPage;
  void *base = heapBase + ((sizeof(memArea_t)/AIGN_SIZE) + 1)*(AIGN_SIZE);  
  /*Mem Area struct init*/
  memArea->pIdleMapBase =(memBlock_t*)base;
  memArea->idleBlockNum = 1;
  memArea->idleSize =AIGN_SIZE * ((MALLOC_USE_MEM_SIZE - sizeof(memArea_t) - sizeof(memBlock_t))/AIGN_SIZE);

  memArea->pUsingMapBase = NULL;
  memArea->usingBlockNum = 0;
  memArea->usingSize = sizeof(memBlock_t);
  
  memArea->pBase = base;
  memArea->pTop = (void *)((char *)base + memArea->idleSize + sizeof(memBlock_t) - 1);

  /*first mem block init*/
  memBlock_t* firstIdleBlock = firstPage + ((sizeof(memArea_t)/AIGN_SIZE) + 1)*(AIGN_SIZE);  
  firstIdleBlock->pNext = NULL;
  firstIdleBlock->size = AIGN_SIZE * ((MALLOC_USE_MEM_SIZE - sizeof(memArea_t) - sizeof(memBlock_t))/AIGN_SIZE - 1);
}
