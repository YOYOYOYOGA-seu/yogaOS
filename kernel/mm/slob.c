/*
 * @Author Shi Zhangkun
 * @Date 2020-11-16 03:35:17
 * @LastEditTime 2022-05-06 15:52:55
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/kernel/mm/slob.c
 */
#include "mm.h"
#include "page.h"
#include "yogaOS/list.h"
#include "yogaOS/types.h"
#include "kernel.h"
#define PAGE_SIZE       0x1000
#define PAGE_SIZE_ORDER 12

#define SLOB_MINI_SIZE  256
#define SLOB_MID_SIZE   1024
#define SLOB_MAX_SIZE   (PAGE_SIZE - sizeof(slobBlock_t))

#define SLOB_LIST_MINI  0
#define SLOB_LIST_MID   1
#define SLOB_LIST_LARGE 2
#define SLOB_LIST_NUM   SLOB_LIST_LARGE + 1
/* 
 * slobPage using the useless area of page_t to record slob msg 
 */
typedef struct slobPage{
  union {
    struct {
			miniListItem_t(struct slobPage) lru;   /* placeholder ,page desc lru */
      uint32_t flag:8;        /* flags for other use */
      uint32_t index:24;     /* placeholder ,page desc index */           
			int16_t units;       /* free bolcks' counts */
      int16_t firstFree;    /* firstFree block's index， -1 respect null */
		};
    page_t page;
  };
}slobPage_t;

/* 
 * slob block description
 */
typedef struct {
  uint16_t inUse:1;
  uint16_t units:15;            /* continuous free block num,  negative respect in use */
  int16_t  nextFree;        /* firstFree block's index， -1 respect null */
}slobBlock_t;

typedef miniList_t(slobPage_t) slobPageList_t;

const size_t SLOB_SIZE_LIMIT[SLOB_LIST_NUM] = {256,1024,PAGE_SIZE - sizeof(slobBlock_t)};
slobPageList_t slobPageList[SYSTEM_ZONE_NUM][SLOB_LIST_NUM] = {{{0,NULL},{0,NULL},{0,NULL}},{{0,NULL},{0,NULL},{0,NULL}}};
pageList_t wholeUsingPageList[SYSTEM_ZONE_NUM] = {{0,NULL},{0,NULL}};
extern zone_t sysMemZone[SYSTEM_ZONE_NUM];




/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
inline void* slob_page_alloc(slobPageList_t *usingList,zoneIndex_t zone)
{
  slobBlock_t* addr = page_allocOne((pageList_t*)usingList, zone);
  if(addr != NULL)
  {
    addr->inUse = 0;
    addr->units = SLOB_MAX_SIZE/sizeof(slobBlock_t);
    addr->nextFree = -1;
    usingList->firstItem->lru.pPrevious->units = addr->units;
    usingList->firstItem->lru.pPrevious->flag |= PAGE_FLAG_SLOB_MASK;
    usingList->firstItem->lru.pPrevious->firstFree = 0;
  }
  return addr;
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
inline error_t slob_page_free(slobPage_t *ptr ,zoneIndex_t zone)
{
  page_t* page = (page_t*)ptr;
  page->flag &= ~(PAGE_FLAG_SLOB_MASK);
  page->bOrder = 0;
  *(uint8_t*)(&page->fatherZone) = zone;
  page->__left_16 = 0;
  return page_recycleOne(page);
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
inline void* slob_getPageAddr(const slobPage_t* page, zoneIndex_t zone)
{
  return (void*)((page->index<<PAGE_SIZE_ORDER) + sysMemZone[zone].linearBase);
}

void slob_init()
{
  
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void* slob_AllocSerachInPage(slobPage_t * page, const size_t blkNum, zoneIndex_t zone)
{
  volatile slobBlock_t* block = slob_getPageAddr(page, zone); 
  if(blkNum <= page->units)
  {
    int16_t index = page->firstFree;
    int16_t last = -1;
    while(index >= 0 && index < PAGE_SIZE/sizeof(slobBlock_t))
    {
      if(block[index].units > blkNum) // can be divide
      {
        block[index + blkNum + 1].units = block[index].units - (blkNum + 1);
        block[index + blkNum + 1].nextFree = block[index].nextFree;
        block[index].inUse = 1; //in use
        block[index].units = blkNum;
        block[index].nextFree = -1;
        if(last < 0)
          page->firstFree = index + blkNum + 1;
        else
          block[last].nextFree = index + blkNum + 1;

        page->units -= blkNum + 1;
        return (void*)(&block[index + 1]);
      }
      else if(block[index].units = blkNum)
      {
        block[index].inUse = 1; //in use
        if(last < 0)
          page->firstFree = block[index].nextFree;
        else
          block[last].nextFree = block[index].nextFree; 
        
        page->units -= blkNum;
        return (void*)(&block[index + 1]);
      }
      last = index;
      index = block[index].nextFree;
    }
  }
  return NULL;
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void* slob_allocateLoop(size_t size, unsigned int index, zoneIndex_t zone)
{
  if(index >= SLOB_LIST_NUM || size > SLOB_SIZE_LIMIT[index] || zone >= SYSTEM_ZONE_NUM)
    return NULL;
  if(slobPageList[zone][index].firstItem == NULL)
  {
    slob_page_alloc(&slobPageList[zone][index],zone);
  }
  void * ret = NULL;
  slobPage_t * page = slobPageList[zone][index].firstItem;
  const size_t blkNum = size/sizeof(slobBlock_t) + (size%sizeof(slobBlock_t) == 0?0:1);

  for(int i = 0; i < slobPageList[zone][index].value && page != NULL; i++)
  {
    ret = slob_AllocSerachInPage(page,blkNum,zone);
    if(ret != NULL)
      return ret;
    page = page->lru.pNext;
  }
  
  /* no suitable block in the page list, then apply for a new slobPage*/
  page =  slob_page_alloc(&slobPageList[zone][index],zone);
  if(page == NULL)
    return NULL;
  return  slob_AllocSerachInPage(page,blkNum,zone);
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void* slob_allocate(size_t size, zoneIndex_t zone)
{
  if(size > SLOB_MAX_SIZE || size == 0)
    return NULL;
  
  if(size > SLOB_MID_SIZE)  //
  {
    return slob_allocateLoop(size, SLOB_LIST_LARGE, zone);
  }
  if(size > SLOB_MINI_SIZE)  //
  {
    return slob_allocateLoop(size, SLOB_LIST_MID, zone);
  }
  else
  {
    return slob_allocateLoop(size, SLOB_LIST_MINI, zone);
  }

}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void slob_recycle(void* ptr,zoneIndex_t zone)
{
  int idx = ((uint32_t)ptr - sysMemZone[zone].linearBase)/PAGE_SIZE;
  if((uint32_t)ptr % sizeof(slobBlock_t) != 0 || idx < 0 || idx >= sysMemZone[zone].managedPages)
    goto SLOB_FREE_IVD_PTR;
  slobPage_t *descPtr = (slobPage_t*)sysMemZone[zone].pPageDescArray;
  if(descPtr[idx].flag & PAGE_FLAG_SLOB_MASK == 0)
    goto SLOB_FREE_OUT_OF_AREA;
  
  slobBlock_t *blockArry = (slobBlock_t *)((uint32_t)ptr & ~(PAGE_SIZE - 1));
  int itrBlkTof = ((uint32_t)(ptr - (void*)2) & (PAGE_SIZE - 1))/sizeof(slobBlock_t);
  if(blockArry[itrBlkTof].inUse != 1)
     goto SLOB_FREE_IVD_PTR;

  blockArry[itrBlkTof].inUse = 0;
  blockArry[itrBlkTof].nextFree = -1;
  descPtr[idx].units += blockArry[itrBlkTof].units;
  int itrLast = -1;  //double ptr to traverse and operate the idle pageblock list(itr and itrLast)
  for(int itr = descPtr[idx].firstFree; itr >= 0 && itr < PAGE_SIZE/sizeof(slobBlock_t) ;itr = blockArry[itr].nextFree)
  {
    if(itr > itrBlkTof)
    {
      if(blockArry[itrBlkTof].units + 1 + itrBlkTof == itr) //can merge two block
      {
        blockArry[itrBlkTof].nextFree = blockArry[itr].nextFree;
        blockArry[itrBlkTof].units += blockArry[itr].units + 1;
        descPtr[idx].units += 1;
      }
      else
      {
        blockArry[itrBlkTof].nextFree = itr;
      }
      break;
    }
    itrLast = itr;
  }
  if(itrLast < 0)
  {
    descPtr[idx].firstFree = itrBlkTof;
  }
  else
  {
    if(blockArry[itrLast].units + 1 + itrLast == itrBlkTof) // can merge two block
    {
      blockArry[itrLast].nextFree = blockArry[itrBlkTof].nextFree;
      blockArry[itrLast].units += blockArry[itrBlkTof].units + 1;
      descPtr[idx].units += 1;
    }
    else
    {
      blockArry[itrLast].nextFree = itrBlkTof;
    }
  }
  
  if(descPtr[idx].units >= SLOB_MAX_SIZE/sizeof(slobBlock_t)) // all blocks in this slob page are freed
    slob_page_free(&descPtr[idx],zone);
  
  return;

SLOB_FREE_IVD_PTR:
  panic("slob_recycle: invild ptr.");
SLOB_FREE_OUT_OF_AREA:
  panic("slob_recycle: area not in a slob page.");
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void* slob_malloc(size_t size,zoneIndex_t zone)
{
  if(size > SLOB_MAX_SIZE)
  {
    int needPage = 0;
    needPage = (size/PAGE_SIZE) + ((size%PAGE_SIZE != 0)?1:0);
    if(needPage > (1 << BUDDY_MAX_ORDER))
      return NULL;
    int order = -1;
    while (needPage != 0) //caculate order
    {
      needPage = needPage >> 1;
      order ++;
    }
    return page_allocByOrder(&wholeUsingPageList[zone],zone,order);
  }
  else
  {
    return slob_allocate(size, zone);
  }
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void slob_free(void* ptr, zoneIndex_t zone)
{
   if(ptr < (void*)sysMemZone[zone].linearBase || 
    ptr > (void*)(sysMemZone[zone].linearBase + sysMemZone[zone].managedPages*PAGE_SIZE))
    panic("slob_free: invild ptr (not allocated by kmalloc).");
  
  
  if(((uint32_t)ptr - sysMemZone[zone].linearBase)%PAGE_SIZE == 0) // kmalloc by whole pages(not from slob)
  { // becasue of the slobBlock struct, a ptr allocated from slob_allocate never align by page.
    page_t* temp = NULL;
    int idx = ((uint32_t)ptr - sysMemZone[zone].linearBase)/PAGE_SIZE;
    miniList_matchMtoV(&wholeUsingPageList[zone],temp,index,==,idx,lru);
    if(temp == NULL)
    {
      panic("slob_free: double free or haven't been allocated.");
    }
    page_recycleOne(temp);
  }
  else //from slob
  {
    slob_recycle(ptr,zone);
  }
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void* kmalloc(size_t size)
{
  void* ret = slob_malloc(size,IDLE_AREA);
  if (ret == NULL) panic("[kernerl] kmalloc failed.\n\r");
  return ret;
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void* fmalloc(size_t size)
{
  void* ret = slob_malloc(size,HS_CACHE);
  if (ret == NULL) panic("[kernerl] fmalloc failed.\n\r");
  return ret;
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void kfree(void* ptr)
{
  slob_free(ptr,IDLE_AREA);
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void ffree(void* ptr)
{
  slob_free(ptr,HS_CACHE);
}