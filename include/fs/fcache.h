/*
 * @Author Shi Zhangkun
 * @Date 2020-12-28 15:23:21
 * @LastEditTime 2020-12-31 16:03:12
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/fs/fcache.h
 */
#ifndef __FS_CACHE_H
#define __FS_CACHE_H
#include "yogaOS/types.h"
#include "yogaOS/list.h"
#define FCACHE_ALLOC_UNIT         0x100


#define FCACHE_BLOCK_256_OD       0
#define FCACHE_BLOCK_512_OD       1
#define FCACHE_BLOCK_1024_OD      2
#define FCACHE_BLOCK_2048_OD      3
#define FCACHE_BLOCK_4096_OD      4
#define FCACHE_BLOCK_MAX_ORDER    FCACHE_BLOCK_4096_OD
/**
 * vfsBlock, mapping the block in device(like hard disk) to fs cache block
 */
typedef struct vfsBlockHead{
  uint32_t dirt:1;
  uint32_t blockNum:31; /* block number in real device */
  void* ptr; /* used to store the block alloced by fs cache */
}vfsBlockHead_t;

typedef struct{
  union {
    void * pMap;
    uint8_t * pMap_1024;
    uint16_t * pMap_2048;
    uint32_t * pMap_4096;
  };
  const uint32_t totalBlocks;
  const uint32_t fcacheMapSize;
  void* fcacheBase;
}fcacheMap_t;


typedef struct fcacheBlkDesc{
  miniListItem_t(struct fcacheBlkDesc) lru;
    /* after alloc this point to the blk memory directly */
  uint8_t order;
  uint8_t inUse;
  uint16_t index;
  void *ptr;
}fcacheBlkDesc_t;

typedef miniList_t(fcacheBlkDesc_t) fcacheBlkDescList_t;
typedef struct{
  fcacheBlkDescList_t freeBlock[FCACHE_BLOCK_MAX_ORDER + 1];
  
  fcacheBlkDesc_t* blkDescTable;
  const uint32_t totalBlocks;  /* uint: bytes */
  uint32_t freeBlocks;
  
  const uint32_t blkSize;
  void* fcacheBase;
}fcacheZone_t;
/* ------- Arch relevant function (defined in arch/xxx/xxx/xxx.c) ----------------- */
size_t fcache_getCacheSize();  //the size must be the multiple of both max fcache block size and system page size
/* ------------------------- function definition ---------------------- */
error_t fcache_init(void);
void* fcache_alloc(size_t size, fcacheBlkDescList_t* usingList);
void fcache_free(fcacheBlkDesc_t* blk);
void fcache_freeList(fcacheBlkDescList_t *usingList);
#endif