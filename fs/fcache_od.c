/*
 * @Author Shi Zhangkun
 * @Date 2020-12-28 15:22:25
 * @LastEditTime 2020-12-30 10:56:43
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/fs/fcache.c
 */


#include "fcache.h"
#include "errno.h"
#include "string.h"


fcacheMap_t cacheMap = {.pMap = NULL, .totalBlocks = 0, .fcacheMapSize = 0, .fcacheBase = NULL,};
extern int enterSystemCall(int vector,int arg_1, int arg_2, int arg_3);











error_t fcache_init(void)
{
  *((uint32_t*)&cacheMap.totalBlocks) = fcache_getCacheSize();
  if(cacheMap.totalBlocks == 0)
    return EPERM;
  cacheMap.fcacheBase = (void*)enterSystemCall(SYS_MALLOC_VECTOR, 0, cacheMap.totalBlocks, 0);
  if(cacheMap.fcacheBase == NULL)
    return EPERM;
  
  *((uint32_t*)&cacheMap.fcacheMapSize) = cacheMap.totalBlocks/(FCACHE_ALLOC_UNIT*8);
  cacheMap.pMap = (void*)enterSystemCall(SYS_MALLOC_VECTOR, 0, cacheMap.fcacheMapSize, 0);
  memset(cacheMap.pMap,0,cacheMap.fcacheMapSize);
  return ENOERR;
}

void* fcache_alloc(uint32_t order)
{
  if(order > FCACHE_BLOCK_MAX_ORDER)
    return NULL;
  

  if(order <= FCACHE_BLOCK_1024_OD)
  {
    uint8_t flag = 0;
    for(uint32_t i = 0; i < cacheMap.fcacheMapSize; i++)
    {
      for(uint32_t j  = 0; j < 8/(1<<order); j++)
      {
        if(cacheMap.pMap_1024[i]&(((1<<(order + 1))-1)<<(j*(1<<order))) == 0)
        {
          cacheMap.pMap_1024[i] |= (((1<<(order + 1))-1)<<(j*(1<<order)));
          return  cacheMap.fcacheBase + (i*8 + j)*(FCACHE_ALLOC_UNIT<<order);
        }
      }
    }
  }
  else if(order == FCACHE_BLOCK_2048_OD)
  {
    for(uint32_t i = 0; i < cacheMap.fcacheMapSize/sizeof(uint16_t); i++)
    {
      if(cacheMap.pMap_2048[i] == 0)
      {
        cacheMap.pMap_2048[i] = 0xFFFF;
        return cacheMap.fcacheBase + i*(FCACHE_ALLOC_UNIT<<FCACHE_BLOCK_2048_OD); 
      }
    }
  }
  else if(order == FCACHE_BLOCK_4096_OD)
  {
    for(uint32_t i = 0; i < cacheMap.fcacheMapSize/sizeof(uint32_t); i++)
    {
      if(cacheMap.pMap_4096[i] == 0)
      {
        cacheMap.pMap_4096[i] = 0xFFFFFFFF;
        return cacheMap.fcacheBase + i*(FCACHE_ALLOC_UNIT<<FCACHE_BLOCK_4096_OD); 
      }
    }
  }

  return NULL;
}