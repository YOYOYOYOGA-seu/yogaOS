/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 03:00:02
 * @LastEditTime 2020-02-29 08:03:49
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/sched_x86.h
 */
#ifndef __SCHED_X86_H
#define __SCHED_X86_H

#include "type.h"
#include "segment.h"
#include "sched.h"
#include "errno.h"
/* ------------------------ type define --------------------------- */
typedef struct{
  uint32_t gs;
  uint32_t fs;
  uint32_t es;
  uint32_t ds;
  uint32_t edi;
  uint32_t esi;
  uint32_t ebp;
  uint32_t kernel_esp;
  uint32_t ebx;
  uint32_t edx;
  uint32_t ecx;
  uint32_t eax;
  uint32_t retaddr;
  uint32_t eip;
  uint32_t cs;
  uint32_t eflags;
  uint32_t esp;
  uint32_t ss;
}x86_stackFrame_t;

typedef struct{
  uint32_t backlink;  /* high 16bit zero */
  uint32_t esp0;
  uint32_t ess0;      /* high 16bit zero */
  uint32_t esp1;
  uint32_t ess1;      /* high 16bit zero */
  uint32_t esp2;
  uint32_t ess2;      /* high 16bit zero */
  uint32_t cr3;
  uint32_t eip;
  uint32_t flags;
  uint32_t eax;
  uint32_t ecx;
  uint32_t edx;
  uint32_t ebx;
  uint32_t esp;
  uint32_t ebp;
  uint32_t esi;
  uint32_t edi;
  uint32_t es;      /* high 16bit zero */
  uint32_t cs;      /* high 16bit zero */
  uint32_t ss;      /* high 16bit zero */
  uint32_t ds;      /* high 16bit zero */
  uint32_t fs;      /* high 16bit zero */
  uint32_t gs;      /* high 16bit zero */
  uint32_t ldt;     /* high 16bit zero */
  uint16_t trap;
  uint16_t iobase;
}TSS_t;

typedef struct{
  TSS_t tss;
  memSegDesc_t ldt[INIT_LDT_NUM];//ldt must be the first member,(under PCB struct in memory addr)
  uint16_t selLDT;    //don't used 
  uint16_t selLDTData;
  uint16_t selLDTCode;
  x86_stackFrame_t * pStackKernel;
  uint32_t ring0Stack_SP;  //save esp , for task switch
  
}x86_taskStruct_t;

#define INIT_EFLAGS 0x1202
#endif
