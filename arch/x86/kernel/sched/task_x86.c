/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 02:59:19
 * @LastEditTime 2020-03-08 10:03:26
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/kernel/sched/task_x86.c
 */
#include "sched_x86.h"
#include "page_x86.h"
#include "sched.h"
#include "type.h"
#include "errno.h"
#include "segment.h"
#include "mm_page.h"
#include "string.h"


/**
 * @brief  init the arch relevant struct in PCB
 * @note  x86 arch, contain LDT, TSS, LDT_selector
 * @param {PCB_t *} pPCB
 *        {void (*)(void)} taskFunc: point to the entry of task code
 * @retval error_t
 */
error_t task_initPCBArchRelevant(PCB_t *pPCB, void (*taskFunc)(void))
{
  uint32_t i;
  x86_taskStruct_t *p;
  pPCB->pArchRelvant = (void *)((uint32_t)pPCB + sizeof(PCB_t));
  p = (x86_taskStruct_t *)pPCB->pArchRelvant;
  p->pStackKernel = (x86_stackFrame_t *)((uint32_t)pPCB + PAGE_SIZE - sizeof(x86_stackFrame_t));
  mm_initDesc(&p->ldt[0], (uint32_t)NULL, 0,0,0,0);
  /*
  if(pPCB->prio <= SCHED_SYS_STASK_PRIO_N) //system task, code is in system space
  {
    //data&stack, D/B must = 1, stack access using eax(32bit)
    mm_initDesc(&p->ldt[1], (uint32_t)NULL, 0xffffffff,DESC_DPL_1,DESC_TYPE_RW,1); 
    mm_initDesc(&p->ldt[2], (uint32_t)NULL, 0xffffffff,DESC_DPL_1,DESC_TYPE_C,1);
    p->selLDTData = 0x08|SEL_TI_MASK|DESC_DPL_1;
    p->selLDTCode = 0x10|SEL_TI_MASK|DESC_DPL_1;
  }
  */
   //user task 
  mm_initDesc(&p->ldt[1], (uint32_t)NULL, 0xffffffff,DESC_DPL_3,DESC_TYPE_RW,1); 
  mm_initDesc(&p->ldt[2], (uint32_t)NULL, 0xffffffff,DESC_DPL_3,DESC_TYPE_C,1);
  p->selLDTData = 0x08|SEL_TI_MASK|DESC_DPL_3;
  p->selLDTCode = 0x10|SEL_TI_MASK|DESC_DPL_3;
  
  if(pPCB->prio <= 1) //init task, now prio 0 respect system task, don't have any father task
  {
    p->pStackKernel->gs = SEL_GDT_VIDEO;
    p->pStackKernel->fs = p->selLDTData;
    p->pStackKernel->es = p->selLDTData;
    p->pStackKernel->ds = p->selLDTData;
    p->pStackKernel->edi = 0;
    p->pStackKernel->esi = 0;
    p->pStackKernel->ebp = 0;
    p->pStackKernel->kernel_esp = PCB_BASE_ADDR + PAGE_SIZE - sizeof(x86_stackFrame_t);
    p->pStackKernel->ebx = 0;
    p->pStackKernel->edx = 0;
    p->pStackKernel->ecx = 0;
    p->pStackKernel->eax = 0;
    p->pStackKernel->retaddr = 0;
    p->pStackKernel->eip = (uint32_t)taskFunc;
    p->pStackKernel->cs = p->selLDTCode;
    p->pStackKernel->eflags = INIT_EFLAGS;
    p->pStackKernel->esp = TASK_STACK_BASE;
    p->pStackKernel->ss = p->selLDTData;
  }
  else //not the first task
  {
    /* code */
  }
  p->ring0Stack_SP = TASK_RING_0_STACK_BASE - sizeof(x86_stackFrame_t);
  p->tss.esp0 = PCB_BASE_ADDR + PAGE_SIZE;
  p->tss.ess0 = SEL_GDT_GLOBAL_DATA;
  return ENOERR;
}

/**
 * @brief init task page table and init task linear address space
 * @note  
 * @param {PCB_t *} pPCB
 * @retval error_t
 */
error_t task_initTaskPage(PCB_t * pPCB)
{
  pageTblItem_t *pL1;
  pageTblItem_t *pL2;
  pageTblItem_t *pL3;
  pL1 = pPCB->L1PageTbl;
  
  memcpy((void *)pL1,(const void *)SYS_PAGE_DIR_BASE_ADDR, PAGE_SIZE);
  //alloc phy mem for PCB ring0 stack, page dir, task use page table 
  pL2 = mm_allocOnePage(&pPCB->usingPageList);
  pL2[0] = pToPhy(pPCB)|PTE_P|PTE_RW|PTE_US;
  pL2[1] = pToPhy(pL1)|PTE_P|PTE_RW|PTE_US;
  pL1[PCB_BASE_ADDR>>22] = pToPhy(pL2)|PDE_P|PDE_RW|PDE_US;

  //alloc phy mem for page table which describe the task stack space
  pL2 = mm_allocOnePage(&pPCB->usingPageList);
  pL2[PAGE_SIZE/sizeof(pageTblItem_t) - 1] = pToPhy(pPCB->pStack)|PTE_P|PTE_RW|PTE_US;
  pL1[0] = pToPhy(pL2)|PDE_P|PDE_RW|PDE_US;

  return ENOERR;
  
}
