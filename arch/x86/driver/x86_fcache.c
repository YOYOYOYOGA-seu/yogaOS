/*
 * @Author Shi Zhangkun
 * @Date 2020-12-29 23:11:36
 * @LastEditTime 2022-04-13 17:05:01
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/arch/x86/driver/x86_fcache.c
 */

#include "fs/fcache.h"
#include "address.h"
#include "mm.h"
/**
 * @brief  
 * @note  return the suitable fcache size 
 * @param {*}
 * @retval none
 */
size_t fcache_getCacheSize(void)
{
  uint32_t size = 0;
  for(int i = 8*sizeof(uint32_t); i > PAGE_SIZE_ORDER&& ((1<<i)>(FCACHE_ALLOC_UNIT<<FCACHE_BLOCK_MAX_ORDER)); i--)
  {
    if((SYS_FILE_BUFF_SIZE& (1 << i)) != 0)
    {
      size = 1 << i;
      if(i >= BUDDY_MAX_ORDER + PAGE_SIZE_ORDER)  // max fs cache size (limited by the max order of buddy system)
        size = 1 << (PAGE_SIZE_ORDER + BUDDY_MAX_ORDER);
      if(size > ((SYS_FILE_BUFF_SIZE*3)/4))
        size /= 2;
      break;
    }
  }
  return size;
}