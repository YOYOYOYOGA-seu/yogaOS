/*
 * @Author Shi Zhangkun
 * @Date 2020-02-28 04:20:43
 * @LastEditTime 2020-06-27 04:43:00
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/kernel/sched/sched_x86.c
 */

#include "types.h"
#include "errno.h"
#include "sched.h"
#include "page_x86.h"
#include "sched_x86.h"
#include "address.h"
 PCB_t* const pLocalPCB = (void *)PCB_BASE_ADDR;  

void sched_loadFirstTask(PCB_t *pPCB)
{
  uint32_t phyPageDirBase = pToPhy(pPCB->L1PageTbl);
  uint32_t ring0Stack = ((x86_taskStruct_t *)pPCB->pArchRelvant)->ring0Stack_SP;

  __asm__("mov %0, %%cr3;"
          "mov %1, %%esp;"
          "pop %%gs;"
          "pop %%fs;"
          "pop %%es;"
          "pop %%ds;"
          "popal;"
          "add $4, %%esp;"
          "iret"
          :
          :"r"(phyPageDirBase),"r"(ring0Stack)
          );
  
}
/*
void sched_switchToTask(PCB_t *pPCB)
{
  uint32_t phyPageDirBase = pToPhy(pPCB->L1PageTbl);
  __asm__("mov %0, %%cr3"
          :
          :"r"(phyPageDirBase)
          );
}
*/