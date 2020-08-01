/*
 * @Author Shi Zhangkun
 * @Date 2020-02-18 02:35:29
 * @LastEditTime 2020-03-29 02:02:49
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/kernel/init.c
 */
#include "init.h"
#include "start.h"
#include "segment.h"
#include "address.h"
#include "system_x86.h"
#include "page.h"
#include "sched.h"
#include "string.h"
#include "sched_x86.h"
#include "time.h"
#include "io.h"
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
  seg_initGDTStruct();
  seg_addDescToGDT(SYS_PAGE_DIR_BASE_ADDR,SYS_PAGE_DIR_SIZE,0,DESC_TYPE_RW,1);
  seg_addDescToGDT(SYS_PAGE_TBL_BASE_ADDR,SYS_PAGE_TBL_SIZE,0,DESC_TYPE_RW,1);
  // 注意！！！！为了测试tty改成的dpl = 3，之后看到记得改回来！！！！！
  seg_addDescToGDT(VIDEO_MEM_BASE_ADDR,VIDEO_MEM_SIZE,3,DESC_TYPE_RW,1);
  
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
  sel = seg_addDescToGDT(PCB_BASE_ADDR + sizeof(PCB_t) + sizeof(TSS_t),LDT_SIZE,0,DESC_TYPE_LDT,1);
  __asm__("lldt %0"
          :
          :"r"(sel)
          );
  sel = seg_addDescToGDT(PCB_BASE_ADDR + sizeof(PCB_t),sizeof(TSS_t),0,DESC_TYPE_386TSS_A,1);
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
 * @note   partial physical memory(now 16M) space have been 
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
 memset((void *)SYS_PAGE_DIR_BASE_ADDR,0, 4*NUM_OF_TMP_MAP_IN_PAGE_DIR);  //4 item in L1 table ,16M area 
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
  page_initPageDesc();
  disp_string32("Page manager init success!!!\n\0");
}


/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */

void init8254Timer(void)
{
  IO_outByte(0x34,0x43);
  IO_outByte((uint8_t)TIMER_FREQ*SYSTEM_TICK/1000,0x40);
  IO_outByte((uint8_t)((TIMER_FREQ*SYSTEM_TICK/1000)>>8),0x40);
}

