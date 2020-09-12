/*
 * @Author Shi Zhangkun
 * @Date 2020-09-12 02:38:50
 * @LastEditTime 2020-09-12 07:40:23
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/lib/x86_malloc.c
 */

#include "address.h"
/**
 * @brief  get the heap start addr, arch relevant
 * @note  
 * @param {type} none
 * @retval none
 */
void * mem_getHeapLocation(void)
{
  return (void*)TASK_HEAP_START_ADDR;
}