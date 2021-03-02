/*
 * @Author Shi Zhangkun
 * @Date 2020-12-30 10:57:11
 * @LastEditTime 2020-12-31 16:08:16
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/fs/fcache.c
 */
#include "fcache.h"
#include "errno.h"
#include "string.h"
#include "yogaOS/upanic.h"

fcacheZone_t cacheZone;

extern int enterSystemCall(int vector,int arg_1, int arg_2, int arg_3);

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void fcacheZone_deinit(fcacheZone_t* cache)
{
  for(int i = 0;i <= FCACHE_BLOCK_MAX_ORDER; i++)
  {
    cache->freeBlock[i].value = 0;
    cache->freeBlock[i].firstItem = NULL;
  }
  cache->blkDescTable = NULL;
  cache->fcacheBase = NULL;
  *(uint32_t*)&cache->blkSize = FCACHE_ALLOC_UNIT;
  cache->freeBlocks = 0;
  *(uint32_t*)&cache->totalBlocks = 0;
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t fcache_init(void)
{
  fcacheZone_deinit(&cacheZone);
  *((uint32_t*)&cacheZone.totalBlocks) = fcache_getCacheSize()/FCACHE_ALLOC_UNIT;
  cacheZone.freeBlocks = cacheZone.totalBlocks;
  if(cacheZone.totalBlocks == 0)
    return EPERM;
  cacheZone.fcacheBase = (void*)enterSystemCall(SYS_MALLOC_VECTOR, 0, cacheZone.totalBlocks*FCACHE_ALLOC_UNIT, 0);
  if(cacheZone.fcacheBase == NULL)
    return EPERM;

  cacheZone.blkDescTable = (void*)enterSystemCall(SYS_MALLOC_VECTOR, 0, cacheZone.totalBlocks*sizeof(fcacheBlkDesc_t), 0);
  if(cacheZone.blkDescTable == NULL)
    return EPERM;

  fcacheBlkDesc_t* p = cacheZone.blkDescTable;
  uint8_t order;
  uint32_t i;

  for (i = 0; i < cacheZone.totalBlocks; i++)
  {
    p[i].order = 0;
    p[i].index = i; 
    p[i].lru.pNext = NULL;
    p[i].lru.pPrevious = NULL;
    p[i].inUse = 0;
  }
  /* becasue fcache_getCacheSize() must return the multiple size of FCACHE_BLOCK_MAX_ORDER,
   * so all fcache area can be divided by max order block */
  for (i = 0; i < cacheZone.totalBlocks/(1<<FCACHE_BLOCK_MAX_ORDER); i++)
  {
    miniList_insertTail(&cacheZone.freeBlock[order], &p[i*(1<<FCACHE_BLOCK_MAX_ORDER)],lru);
    p[i*(1<<FCACHE_BLOCK_MAX_ORDER)].order = FCACHE_BLOCK_MAX_ORDER;
  }
  cacheZone.freeBlock[FCACHE_BLOCK_MAX_ORDER].firstItem = p;
  cacheZone.freeBlock[FCACHE_BLOCK_MAX_ORDER].value = cacheZone.totalBlocks/(1<<FCACHE_BLOCK_MAX_ORDER);
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void* fcache_alloc(size_t size, fcacheBlkDescList_t* usingList)
{
  int order = 0;
  int i = 0;
  int tempIndex;
  fcacheBlkDesc_t* p;
  switch (size)
  {
  case FCACHE_ALLOC_UNIT<<FCACHE_BLOCK_256_OD:
    order = FCACHE_BLOCK_256_OD;
    break;
  case FCACHE_ALLOC_UNIT<<FCACHE_BLOCK_512_OD:
    order = FCACHE_BLOCK_512_OD;
    break;
  case FCACHE_ALLOC_UNIT<<FCACHE_BLOCK_1024_OD:
    order = FCACHE_BLOCK_1024_OD;
    break;
  case FCACHE_ALLOC_UNIT<<FCACHE_BLOCK_2048_OD:
    order = FCACHE_BLOCK_2048_OD;
    break;
  case FCACHE_ALLOC_UNIT<<FCACHE_BLOCK_4096_OD:
    order = FCACHE_BLOCK_4096_OD;
    break;
  default:
    return NULL;
  }

  for(i = order; i < FCACHE_BLOCK_MAX_ORDER + 1; i++)
  {
    if(cacheZone.freeBlock[i].value > 0)
      break;
    if(i == FCACHE_BLOCK_MAX_ORDER)   //not found a bock can be alloced
      return NULL;
  }
  
  p = miniList_PopHead(&cacheZone.freeBlock[i],lru);
  tempIndex = p->index;
  p->order = order;
  while(i > order)  //divide specify order bock form a high order block
  {
    i--;
    miniList_insertHead(&cacheZone.freeBlock[i],&cacheZone.blkDescTable[tempIndex + (1<<i)],lru);
    cacheZone.blkDescTable[tempIndex + (1<<i)].order = i;
  }
  cacheZone.freeBlocks-= 1<<order;
  miniList_insertHead(usingList,p,lru);
  return cacheZone.fcacheBase + (p->index*FCACHE_ALLOC_UNIT);
}

void fcache_free(fcacheBlkDesc_t* blk)
{
  if( blk == NULL||(!(blk->index >= 0 && blk->index < cacheZone.totalBlocks)))
    upanic("fcache_free: invild ptr");

  fcacheBlkDesc_t *p = NULL;
  uint8_t order;
  uint32_t buddyIndex;
  cacheZone.freeBlocks += 1<<blk->order;
  for(order= blk->order; order < FCACHE_BLOCK_MAX_ORDER ; order++)
  {
    buddyIndex = blk->index^(1<<order); /* get buddy block desc index */
    miniList_matchMtoV(&cacheZone.freeBlock[order],p,index,==,buddyIndex,lru);
    if(p == NULL)
    {
      break;
    }
    else
    {
      miniList_remove(&cacheZone.freeBlock[order],p,lru);
      if((p->index & (1 << order)) == 0)
        blk = p;
      blk->order = order + 1;
    }
  }
  miniList_insertHead(&cacheZone.freeBlock[order],blk,lru);
}

/**
 * @brief  
 * @note  
 * @param {fcacheBlkDescList_t} *usingList
 * @retval none
 */
void fcache_freeList(fcacheBlkDescList_t *usingList)
{
  if( usingList == NULL) return;
  fcacheBlkDesc_t * blk;
  while(usingList->value > 0)
  {
    blk = miniList_PopHead(usingList,lru);
    fcache_free(blk);
  }
}