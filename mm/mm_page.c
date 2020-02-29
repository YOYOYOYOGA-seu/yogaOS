/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 05:13:44
 * @LastEditTime 2020-02-26 23:33:04
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/mm/mm_page.c
 */

#include "mm_page.h"
#include "type.h"
#include "errno.h"
/* ------------------------ varible declare --------------------------- */
static pageList_t idlePageList; 
static uint32_t pageListSize;
static uint32_t idleMemPhyrBase;
static uint32_t idleMemLinearBase;

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void mm_initPageManage(void)
{
  uint16_t i;
  uint32_t value;
  page_t * p;
  
  idlePageList.pFirstItem = mm_locatePageList(&pageListSize, &idleMemPhyrBase, &idleMemLinearBase);
  idlePageList.numberOfItem = pageListSize;
  p = idlePageList.pFirstItem;
  value = idleMemPhyrBase;
  for(i = 0; i < pageListSize; i++)
  {
    p->value = value;  //the value stored physical addr of the page be managed
    p->pOwner = NULL;
    p->pNext = p + 1;
    p = p->pNext;
    value += 0x1000; 
  }

  p = p - 1;
  p->pNext = NULL;
  
}

/**
 * @brief  
 * @note  
 * @param {pageList_t *} usingList :caller provide 
 * @retval NULL :fail
 *         linear address of this idle page(= phy addr + sys_base_linear_addr)
 */

void *mm_allocOnePage(pageList_t *usingList)
{
  uint32_t i;
  page_t * p = idlePageList.pFirstItem;
  
  if(p != NULL)
  {
    idlePageList.pFirstItem = p ->pNext;
    p -> pNext = usingList->pFirstItem;
    usingList->pFirstItem = p;

    usingList->numberOfItem ++;
    idlePageList.numberOfItem --;
    return (void *)(p->value + idleMemLinearBase - idleMemPhyrBase); 
    //return the pointer to the space of the physical map 
  }
  return NULL;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t mm_checkIdleMemNum(uint32_t allocNum)
{
  return (allocNum <= idlePageList.numberOfItem ? ENOERR:ENOSPC);
}