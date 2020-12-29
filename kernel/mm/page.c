/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 05:13:44
 * @LastEditTime 2020-12-12 20:33:02
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/mm/page.c
 */
#include "mm.h"
#include "page.h"
#include "yogaOS/types.h"
#include "errno.h"
#include "kernel.h"

#define PAGE_SIZE_ORDER 12
/* ------------------------ varible declare --------------------------- */
extern zone_t sysMemZone[SYSTEM_ZONE_NUM];


/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void page_initPageDesc(zoneIndex_t zone)
{
  uint32_t i;
  int tempIndex;
  uint32_t start;
  uint32_t value;
  uint32_t end;
  page_t *p;
  page_t *pnt;
  uint8_t order;

  
  p = sysMemZone[zone].pPageDescArray;
  start = sysMemZone[zone].phyBase>>PAGE_SIZE_ORDER;
  end = start + sysMemZone[zone].managedPages;
  value = start;
  //value = (1 << BUDDY_MAX_ORDER) - (start & ((1 << BUDDY_MAX_ORDER) - 1));
  /* init page mm desc structs in page desc array*/
  for (i = 0; i < sysMemZone[zone].managedPages; i++)
  {
    *(uint8_t*)&p[i].fatherZone = zone;
    p[i].index = i; //the value stored physical addr of the page be managed
    p[i].flag = 0;
    p[i].bOrder = 0;
    p[i].lru.pNext = NULL;
    p[i].lru.pPrevious = NULL;

  }
  /*determine max order */
  for(order = BUDDY_MAX_ORDER; order > 0; order-- )
  {
    if((start + (1<<order)) <= end)
      break;
  }
  sysMemZone[zone].maxFreeOrder = order;
  
  if(value & ((1<<order) - 1) != 0)
    value += 1<<order - (start &((1<<order) - 1));

  tempIndex = value - start;
  
   /* load the max order block */
  
  for (; tempIndex <= sysMemZone[zone].managedPages - (1 << order); tempIndex += (1 << order) )
  {
    miniList_insertTail(&sysMemZone[zone].freeBlock[order],&p[tempIndex],lru);
    p[tempIndex].bOrder = order;
  }
  /* load the orphan block(with out a buddy) in the tail*/
  while (order > 0)
  {
    if(tempIndex >= sysMemZone[zone].managedPages)
      break;
    order--;
    if(tempIndex + (1<<order) <= sysMemZone[zone].managedPages)
    {
      miniList_insertTail(&sysMemZone[zone].freeBlock[order], &p[tempIndex],lru);
      p[tempIndex].bOrder = order;
      tempIndex += 1<<order;
    }
  }
  /* load the orphan block(with out a buddy) in the tail*/
  tempIndex = value - start;
  order =  sysMemZone[zone].maxFreeOrder;
  while (order > 0)
  {
    if(tempIndex <= 0)
      break;
    order--;
    if(tempIndex >= 1 << order )
    {
      tempIndex -= 1<<order;
      miniList_insertTail(&sysMemZone[zone].freeBlock[order], &p[tempIndex],lru);
      p[tempIndex].bOrder = order;
    }
  }
  
 /* load the orphan block(with out a buddy) */
}

/**
 * @brief  
 * @note  
 * @param {pageList_t *} usingList :caller provide 
 * @retval linear address of this idle page in linear relocate area(= phy addr + sys_base_linear_addr),fail with NULL
 */
void *page_allocByOrder(pageList_t *usingList, zoneIndex_t zone, uint8_t order)
{ 
  if(order > BUDDY_MAX_ORDER) return NULL;
  int i;
  int tempIndex;
  page_t *p;
  for(i = order; i < BUDDY_MAX_ORDER + 1; i++)
  {
    if(sysMemZone[zone].freeBlock[i].value > 0)
      break;
    if(i == BUDDY_MAX_ORDER)   //not found a bock can be alloced
      return NULL;
  }
  p = miniList_PopHead(&sysMemZone[zone].freeBlock[i],lru);
  tempIndex = p->index;
  p->bOrder = order;
  while(i > order)  //divide specify order bock form a high order block
  {
    i--;
    miniList_insertHead(&sysMemZone[zone].freeBlock[i],&sysMemZone[zone].pPageDescArray[tempIndex + (1<<i)],lru);
    sysMemZone[zone].pPageDescArray[tempIndex + (1<<i)].bOrder = i;
  }
  sysMemZone[zone].freePages-= 1<<order;
  miniList_insertHead(usingList,p,lru);
  return (void*)((p->index<<PAGE_SIZE_ORDER) + sysMemZone[zone].linearBase);
}

/**
 * @brief  recycle a select page to free page
 * @note  Before call this func you must remove the page from the using list manually ! 
 * @param {page_t*} page : point to the page desc
 * @retval error_t
 */
error_t page_recycleOne(page_t* page)
{
  if( page == NULL) return  EFAULT;
  assertk(!(page->fatherZone < SYSTEM_ZONE_NUM));
  assertk(!(page->index >= 0 && \
          page->index < sysMemZone[page->fatherZone].managedPages));
  
  page_t *p = NULL;
  zoneIndex_t zone = (zoneIndex_t)page->fatherZone;
  uint8_t order;
  uint32_t buddyIndex;
  
  sysMemZone[zone].freePages += 1<<page->bOrder;
  /* match if there are free buddy block ,and  merge it to a higher order block */
  for(order= page->bOrder; order < BUDDY_MAX_ORDER ; order++)
  {
    buddyIndex = page->index^(1<<order); /* get buddy block desc index */
    miniList_matchMtoV(&sysMemZone[zone].freeBlock[order],p,index,==,buddyIndex,lru);
    if(p == NULL)
    {
      break;
    }
    else
    {
      miniList_remove(&sysMemZone[zone].freeBlock[order],p,lru);
      if((p->index & (1 << order)) == 0)
        page = p;
      page->bOrder = order + 1;
    }
  }
  
  miniList_insertHead(&sysMemZone[zone].freeBlock[order],page,lru);
  
  return ENOERR;
}
/**
 * @brief  recycle all pages in a using pages list
 * @note  
 * @param {pageList_t *} usingList : point to the using List
 * @retval error_t
 */
error_t page_recycle(pageList_t *usingList)
{
  if( usingList == NULL) return  EFAULT;
  page_t * page;
  while(usingList->value > 0)
  {
    page = miniList_PopHead(usingList,lru);
    page_recycleOne(page);
  }
  return ENOERR;
}
/**
 * @brief  judge if the are enough idle page to alloc
 * @note  only means when alloc page one by one(such as create a task)
 * @param {uint32_t} allocNum : num of applying page
 * @retval error_t
 */
error_t page_checkIdleMemNum(uint32_t allocNum,zoneIndex_t zone)
{
  return (allocNum <= sysMemZone[zone].freePages ? ENOERR : ENOSPC);
}