/*
 * @Author Shi Zhangkun
 * @Date 2020-02-17 21:58:27
 * @LastEditTime 2020-02-26 23:29:52
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/mm/page_x86.c
 */
#include "page_x86.h"
#include "page.h"
#include "system_x86.h"
/**
 * @brief  locate the page manage list address
 * @note   arch relevant 
 * @param {uint32_t *} size     :retval list size
 *        {uint32_t *} phyrBase :retaval managing idle memory base physical address
 *        {uint32_t *}linearBase:retaval managing idle memory base linear address
 * @retval point to the first item of page manage list item
 */
page_t *page_locateList(uint32_t *size, uint32_t *phyrBase, uint32_t *linearBase)
{
  if(sysMessage->idlePageNum < (SYS_PAGE_TBL_SIZE)/4)
    *size = sysMessage->idlePageNum;
  else
    *size = (SYS_PAGE_TBL_SIZE)/4;
    
  *phyrBase = PHY_IDLE_MEM_BASE_ADDR;
  *linearBase = IDLE_MEM_BASE_ADDR;
  return (page_t *)PAGE_MM_LIST_BASE_ADDR;
}