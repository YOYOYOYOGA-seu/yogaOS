/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 05:13:44
 * @LastEditTime 2020-08-01 08:06:26
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/mm/page.c
 */
#include "mm.h"
#include "page.h"
#include "yogaOS/types.h"
#include "errno.h"
/* ------------------------ varible declare --------------------------- */
extern zone_t sysMemZone[SYSTEM_ZONE_NUM];

static uint32_t pageListSize;

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void page_initPageDesc(void)
{
  uint32_t i;
  int tempIndex;
  uint32_t start;
  uint32_t value;
  uint32_t end;
  page_t *p;
  page_t *pnt;
  uint32_t order;

  
  p = sysMemZone[IDLE_AREA].pPageDescArray;
  start = sysMemZone[IDLE_AREA].phyBase>>12;
  end = start + sysMemZone[IDLE_AREA].totalPages;
  value = start;
  //value = (1 << BUDDY_MAX_ORDER) - (start & ((1 << BUDDY_MAX_ORDER) - 1));
  /* init page mm desc structs in page desc array*/
  for (i = 0; i < pageListSize; i++)
  {
    p->index = i; //the value stored physical addr of the page be managed
    p->bOrder = 0;
    p->lru.pNext = NULL;
    p->lru.pPrevious = NULL;
  }
  /*determine max order */
  for(order = BUDDY_MAX_ORDER; order > 0; order-- )
  {
    if((start + (1<<order)) <= end)
      break;
  }
  sysMemZone[IDLE_AREA].maxFreeOrder = order;
  
  if(value > value >> order)
    value += 1<<order - (start &((1<<order) - 1));

  tempIndex = value - start;
  
   /* load the max order block */
  
  for (; tempIndex <= sysMemZone[IDLE_AREA].totalPages - (1 << order); tempIndex += (1 << order) )
  {
    miniList_insertTail(sysMemZone[IDLE_AREA].freeBlock[order],&p[tempIndex],lru);
  }
  /* load the orphan block(with out a buddy) in the tail*/
  while (order > 0)
  {
    if(tempIndex >= sysMemZone[IDLE_AREA].totalPages)
      break;
    order--;
    if(tempIndex + (1<<order) <= sysMemZone[IDLE_AREA].totalPages)
    {
       miniList_insertTail(sysMemZone[IDLE_AREA].freeBlock[order], &p[tempIndex],lru);
      tempIndex += 1<<order;
    }
  }
  /* load the orphan block(with out a buddy) in the tail*/
  tempIndex = value - start;
  order =  sysMemZone[IDLE_AREA].maxFreeOrder;
  while (order > 0)
  {
    if(tempIndex <= 0)
      break;
    order--;
    if(tempIndex >= 1 << order )
    {
      tempIndex -= 1<<order;
      miniList_insertTail(sysMemZone[IDLE_AREA].freeBlock[order], &p[tempIndex],lru);
    }
  }
  /* 进度 ------------------- 2020/8/1 --------------------------- */ 
 /* load the orphan block(with out a buddy) */
  
  start = value >> BUDDY_MAX_ORDER;
  if (start != 0)
  {
    sysMemZone[IDLE_AREA].freeBlock[BUDDY_MAX_ORDER].firstItem = &p[1<<BUDDY_MAX_ORDER];
    for (i = 0; i < start; i++)
    {
      p[1<<BUDDY_MAX_ORDER];
    }
      
  }
}

/**
 * @brief  
 * @note  
 * @param {pageList_t *} usingList :caller provide 
 * @retval NULL :fail
 *         linear address of this idle page(= phy addr + sys_base_linear_addr)
 */
void *page_allocOne(pageList_t *usingList)
{
  uint32_t i;
  page_t *p = idlePageList.pFirstItem;

  if (p != NULL)
  {
    idlePageList.pFirstItem = p->pNext;
    p->pNext = usingList->pFirstItem;
    usingList->pFirstItem = p;

    usingList->numberOfItem++;
    idlePageList.numberOfItem--;
    return (void *)(p->value + idleMemLinearBase - idleMemPhyrBase);
    //return the pointer to the space of the physical map
  }
  return NULL;
}

/**
 * @brief  judge if the are enough idle page to alloc
 * @note  
 * @param {uint32_t} allocNum : num of applying page
 * @retval error_t
 */
error_t page_checkIdleMemNum(uint32_t allocNum)
{
  return (allocNum <= idlePageList.numberOfItem ? ENOERR : ENOSPC);
}