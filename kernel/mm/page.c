/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 05:13:44
 * @LastEditTime 2020-08-09 07:59:31
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


/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void page_initPageDesc(zoneIndex_t index)
{
  uint32_t i;
  int tempIndex;
  uint32_t start;
  uint32_t value;
  uint32_t end;
  page_t *p;
  page_t *pnt;
  uint8_t order;

  
  p = sysMemZone[index].pPageDescArray;
  start = sysMemZone[index].phyBase>>12;
  end = start + sysMemZone[index].totalPages;
  value = start;
  //value = (1 << BUDDY_MAX_ORDER) - (start & ((1 << BUDDY_MAX_ORDER) - 1));
  /* init page mm desc structs in page desc array*/
  for (i = 0; i < sysMemZone[index].totalPages; i++)
  {
    p[i].fatherZone = index;
    p[i].index = i; //the value stored physical addr of the page be managed
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
  sysMemZone[index].maxFreeOrder = order;
  
  if(value & ((1<<order) - 1) != 0)
    value += 1<<order - (start &((1<<order) - 1));

  tempIndex = value - start;
  
   /* load the max order block */
  
  for (; tempIndex <= sysMemZone[index].totalPages - (1 << order); tempIndex += (1 << order) )
  {
    miniList_insertTail(&sysMemZone[index].freeBlock[order],&p[tempIndex],lru);
    p[tempIndex].bOrder = order;
  }
  /* load the orphan block(with out a buddy) in the tail*/
  while (order > 0)
  {
    if(tempIndex >= sysMemZone[index].totalPages)
      break;
    order--;
    if(tempIndex + (1<<order) <= sysMemZone[index].totalPages)
    {
      miniList_insertTail(&sysMemZone[index].freeBlock[order], &p[tempIndex],lru);
      p[tempIndex].bOrder = order;
      tempIndex += 1<<order;
    }
  }
  /* load the orphan block(with out a buddy) in the tail*/
  tempIndex = value - start;
  order =  sysMemZone[index].maxFreeOrder;
  while (order > 0)
  {
    if(tempIndex <= 0)
      break;
    order--;
    if(tempIndex >= 1 << order )
    {
      tempIndex -= 1<<order;
      miniList_insertTail(&sysMemZone[index].freeBlock[order], &p[tempIndex],lru);
      p[tempIndex].bOrder = order;
    }
  }
  
 /* load the orphan block(with out a buddy) */
}

/**
 * @brief  
 * @note  
 * @param {pageList_t *} usingList :caller provide 
 * @retval NULL :fail
 *         linear address of this idle page in linear relocate area(= phy addr + sys_base_linear_addr)
 */
void *page_allocByOrder(pageList_t *usingList, zoneIndex_t index, uint8_t order)
{ 
  if(order > BUDDY_MAX_ORDER) return NULL;
  int i;
  int tempIndex;
  page_t *p;
  for(i = order; i < BUDDY_MAX_ORDER + 1; i++)
  {
    if(sysMemZone[index].freeBlock[i].value > 0)
      break;
    if(i == BUDDY_MAX_ORDER)   //not found a bock can be alloced
      return NULL;
  }
  p = miniList_PopHead(&sysMemZone[index].freeBlock[i],lru);
  tempIndex = p->index;
  p->bOrder = order;
  while(i > order)  //divide specify order bock form a high order block
  {
    i--;
    miniList_insertHead(&sysMemZone[index].freeBlock[i],&sysMemZone[index].pPageDescArray[tempIndex + (1<<i)],lru);
    sysMemZone[index].pPageDescArray[tempIndex + (1<<i)].bOrder = i;
  }
  sysMemZone[index].freePages-= 1<<order;
  miniList_insertHead(usingList,p,lru);
  return (void*)((p->index<<12) + sysMemZone[index].linearBase);
}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t page_recycle(pageList_t *usingList,page_t* page)
{
  if(usingList == NULL || page == NULL) return  EFAULT;
  
  miniList_remove(usingList,page,lru);
  page_t *p = NULL;
  zoneIndex_t zone = (zoneIndex_t)page->fatherZone;
  uint8_t order;
  uint32_t buddyIndex;
  
  /* match if there are free buddy block ,and  merge it to a higher order block */
  for(order= page->bOrder; order < BUDDY_MAX_ORDER + 1; order++)
  {
    buddyIndex = (page->index + (sysMemZone[zone].phyBase)>>12)^(1<<order); /* get buddy block desc index */
    miniList_matchMtoV(&sysMemZone[zone].freeBlock[order],p,index,==,buddyIndex,lru);
    if(p == NULL)
    {
      break;
    }
    else
    {
      miniList_remove(&sysMemZone[zone].freeBlock[order],p,lru);
      /* ?? ------------------- 2020/8/9 --------------------------- */ 
    }
  }
  
  
}
/**
 * @brief  judge if the are enough idle page to alloc
 * @note  only means when alloc page one by one(such as create a task)
 * @param {uint32_t} allocNum : num of applying page
 * @retval error_t
 */
error_t page_checkIdleMemNum(uint32_t allocNum,zoneIndex_t index)
{
  return (allocNum <= sysMemZone[index].freePages ? ENOERR : ENOSPC);
}