/*
 * @Author Shi Zhangkun
 * @Date 2020-02-20 05:11:29
 * @LastEditTime 2020-03-08 09:49:16
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/kernel/interrupt/irq_handler.c
 */
#include "address.h"
#include "type.h"
#include "sched.h"
#include "time.h"
#include "irq.h"
#include "segment.h"
#include "time.h"
extern void disp_string32(char *info);

extern long timeCount;
gateDesc_t * const IDT = (gateDesc_t *)IDT_BASE_ADDR;
void initInterrupt(void)
{
  initGate(&IDT[TIME_IRQ_VECTOR],(uint32_t)timer_IRQhandler,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  initGate(&IDT[SYSTEM_CALL_VECTOR],(uint32_t)system_call,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  //__enableIRQ();
}

void do_timer(void)
{
  timeCount+= SYSTEM_TICK;
  if(timeCount%1000 == 0)
    disp_string32("a\0");
  sched_timeTick();
}