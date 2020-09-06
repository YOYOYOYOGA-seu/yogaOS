/*
 * @Author Shi Zhangkun
 * @Date 2020-02-17 21:58:27
 * @LastEditTime 2020-09-06 00:34:28
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/kernel/mm/mm_x86.c
 */
#include "mm.h"
#include "page_x86.h"
#include "sched.h"
#include "page.h"
#include "system_x86.h"

extern zone_t sysMemZone[SYSTEM_ZONE_NUM];
/**
 * @brief  locate the page manage list address(old vision use,now abandon)
 * @note   arch relevant
 * @param {uint32_t *} size     :retval list size
 * @param {uint32_t *} phyrBase :retaval managing idle memory base physical address
 * @param {uint32_t *}linearBase:retaval managing idle memory base linear address
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
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void page_missing(uint32_t addr)
{
  PCB_t* pPCB = (PCB_t*)PCB_BASE_ADDR;
  uint32_t L2pageIndex;
  uint32_t L1pageIndex;
  pageTblItem_t *pL1;
  pageTblItem_t *pL2 = NULL;
  if(addr < PCB_BASE_ADDR)  // page missing can only occur in user task area
  {
    L1pageIndex = addr >> 22;
    L2pageIndex = (addr >> 12)&0x3FF;
    pL1 = pPCB->L1PageTbl;
    if((pL1[L1pageIndex]&0xFFC00000) == 0)  //L2 page addr is null
    {
      pL2 = page_allocOne(&pPCB->usingPageList,IDLE_AREA);
      pL1[L1pageIndex] = pToPhy(pL2)|PDE_P|PDE_RW|PDE_US;  //L1 page tabe don't restrict dpl
    }
    else
    {
      pL2 = (pageTblItem_t *)phyToLin(pL1[L1pageIndex]&0xFFFFF000);
    }
    pL2[L2pageIndex] = pToPhy(page_allocOne(&pPCB->usingPageList,IDLE_AREA))|PTE_P|PTE_RW|PTE_US;
  }
  __asm__("mov %0, %%cr3;"
          :
          :"r"(pToPhy(pPCB->L1PageTbl))
          );
}
/**
 * @brief  init the zone manager
 * @note  
 * @param {type} none
 * @retval none
 */
void zone_sysZoneInit(void)
{
  /* fs cache zone */
  sysMemZone[FS_CACHE].flag = STATIC;
  sysMemZone[FS_CACHE].phyBase = PHY_FILE_BUFF_BASE_ADDR;
  sysMemZone[FS_CACHE].linearBase = FILE_BUFF_BASE_ADDR;
  sysMemZone[FS_CACHE].freePages = SYS_FILE_BUFF_SIZE >> 12;
  sysMemZone[FS_CACHE].totalPages  = SYS_FILE_BUFF_SIZE >> 12;
  /* fs cache(disk R/W buf)'s mm desc need bootstrap(alloc from fs cache area) */
  sysMemZone[IDLE_AREA].pPageDescArray = NULL; 

  /* idle area zone */
  sysMemZone[IDLE_AREA].flag = DYNAMIC;
  sysMemZone[IDLE_AREA].phyBase = PHY_IDLE_MEM_BASE_ADDR;
  sysMemZone[IDLE_AREA].linearBase = IDLE_MEM_BASE_ADDR;
  if(sysMessage->idlePageNum < (SYS_PAGE_TBL_SIZE)/4)
  {
    sysMemZone[IDLE_AREA].totalPages = sysMessage->idlePageNum;
  }
  else
  {
    sysMemZone[IDLE_AREA].totalPages = (SYS_PAGE_TBL_SIZE)/4;
  }
  sysMemZone[IDLE_AREA].freePages = sysMemZone[IDLE_AREA].totalPages;
  /* idle area(disk R/W buf)'s mm desc are in another area(needn't alloc from idle area) */
  sysMemZone[IDLE_AREA].pPageDescArray = (page_t *)PAGE_MM_LIST_BASE_ADDR;
  
}