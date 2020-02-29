/*
 * @Author Shi Zhangkun
 * @Date 2020-02-18 02:35:29
 * @LastEditTime 2020-02-29 08:05:58
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/kernel/init.c
 */
#include "init.h"
#include "start.h"
#include "segment.h"
#include "address.h"
#include "system_x86.h"
#include "mm_page.h"
#include "sched.h"
#include "string.h"
#include "sched_x86.h"
extern void disp_string32(char *info);
const sysMsg_t *const sysMessage = (const sysMsg_t *)(SYS_MESSAGE_ADDR);
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t initGDT(void)
{
  mm_initGDTStruct();
  mm_addDescToGDT(SYS_PAGE_DIR_BASE_ADDR,SYS_PAGE_DIR_SIZE,0,DESC_TYPE_RW,1);
  mm_addDescToGDT(SYS_PAGE_TBL_BASE_ADDR,SYS_PAGE_TBL_SIZE,0,DESC_TYPE_RW,1);
  mm_addDescToGDT(VIDEO_MEM_BASE_ADDR,VIDEO_MEM_SIZE,0,DESC_TYPE_RW,1);
  
  disp_string32("GDT init success!!!\n\0");
  return ENOERR;
}


/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t initLDT(void)
{
  selector_t  sel;
  sel = mm_addDescToGDT(PCB_BASE_ADDR + sizeof(PCB_t) + sizeof(TSS_t),LDT_SIZE,0,DESC_TYPE_LDT,1);
  __asm__("lldt %0"
          :
          :"r"(sel)
          );
  sel = mm_addDescToGDT(PCB_BASE_ADDR + sizeof(PCB_t),sizeof(TSS_t),0,DESC_TYPE_386TSS_A,1);
  __asm__("ltr %0"
          :
          :"r"(sel)
          );
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t initSegment(void)
{
  error_t flag;
  initGDT();
  initLDT();
  return flag;
  
}
/**
 * @brief  reset the page dir (L1 page) head to zero
 * @note   the whole physical memory space have been 
 *         mapped to the same address in linear address
 *         space before page table init complete,this function
 *         is to reset them in linear address after the whole
 *         physical memory have been mapped to high address area
 *         in linear address space
 * @param {type} none
 * @retval none
 */
void resetPageDir(void)
{
 memset((void *)SYS_PAGE_DIR_BASE_ADDR,0, sysMessage->memSize>>20);
}
/**
 * @brief  init sys
 * @note  
 * @param {type} none
 * @retval none
 */
void initSysMsg(void)
{
  sysMsg_t *p = (sysMsg_t *)sysMessage;
  p->idleMemSize = (p -> memSize) - SYSTEM_RESERVE_AREA_SIZE;
  p->phyPageNum = (p -> memSize)>>12;
  p->idlePageNum = (p->idleMemSize)>>12;
  disp_string32("System message init success!!!\n\0");
}

/**
 * @brief  init some global system message 
 * @note  
 * @param {type} none
 * @retval none
 */
void initMemManage(void)
{
  mm_initPageManage();
  disp_string32("Page manager init success!!!\n\0");
}
