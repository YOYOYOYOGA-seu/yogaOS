/*
 * @Author Shi Zhangkun
 * @Date 2020-02-20 05:11:29
 * @LastEditTime 2020-10-31 06:26:09
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/kernel/interrupt/irq_handler.c
 */
#include "address.h"
#include "yogaOS/types.h"
#include "sched.h"
#include "time.h"
#include "irq.h"
#include "segment.h"
#include "time.h"
#include "io.h"
#include "keyboard.h"
#include "kb_map.h"
#include "kernel.h"
#include "page.h"
#include "system_x86.h"

#define ifExternIRQ(irq) (irq >= EXTERN_IRQ_START && irq <= EXTERN_IRQ_END)
extern void page_fault(void);
extern void __entry_8259A_irq_0(void);
extern void __entry_8259A_irq_1(void);
extern void __entry_8259A_irq_2(void);
extern void __entry_8259A_irq_3(void);
extern void __entry_8259A_irq_4(void);
extern void __entry_8259A_irq_5(void);
extern void __entry_8259A_irq_6(void);
extern void __entry_8259A_irq_7(void);
extern void __entry_8259A_irq_8(void);
extern void __entry_8259A_irq_9(void);
extern void __entry_8259A_irq_10(void);
extern void __entry_8259A_irq_11(void);
extern void __entry_8259A_irq_12(void);
extern void __entry_8259A_irq_13(void);
extern void __entry_8259A_irq_14(void);
extern void __entry_8259A_irq_15(void);
extern void system_call(void);

extern void fault_default(void);
extern void irq_defaultHandler(void);

gateDesc_t * const IDT = (gateDesc_t *)IDT_BASE_ADDR;
void (*ext_irq_handler_table[16])(void) = {irq_defaultHandler};  //extern irq table
/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void irq_enableExt(int irq)
{
  if(!ifExternIRQ(irq))
    return;
  int mask;
  irq -= EXTERN_IRQ_START;
  if(irq < 8 ) // 8259A master
  {
    mask = IO_inByte(IO_PIC1_1);
    mask &= ~(1 << irq);
    IO_outByte(mask,IO_PIC1_1);
  }
  else if(irq < 16)
  {
    irq -= 8;
    mask = IO_inByte(IO_PIC1_1);
    mask &= ~(1 << irq);
    IO_outByte(mask,IO_PIC1_1);
  }
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void irq_disableExt(int irq)
{
  if(!ifExternIRQ(irq))
    return;
  int mask;
  irq -= EXTERN_IRQ_START;
  if(irq < 8) // 8259A master
  {
    mask = IO_inByte(IO_PIC1_1);
    mask |= 1 << irq;
    IO_outByte(mask,IO_PIC1_1);
  }
  else if(irq < 16)
  {
    irq -= 8;
    mask = IO_inByte(IO_PIC1_1);
    mask |= 1 << irq;
    IO_outByte(mask,IO_PIC1_1);
  }
}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void irq_initHandler(void)
{
  seg_initGate(&IDT[PAGE_FAULT],(uint32_t)page_fault,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  /* external interrupt */
  seg_initGate(&IDT[TIMER_IRQ_VECTOR],(uint32_t)__entry_8259A_irq_0,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[KEYBOARD_IRQ_VECTOR],(uint32_t)__entry_8259A_irq_1,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[SERIAL_1_IRQ_VECTOR],(uint32_t)__entry_8259A_irq_3,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[SERIAL_2_IRQ_VECTOR],(uint32_t)__entry_8259A_irq_4,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[LPT2_IRQ_VECTOR],(uint32_t)__entry_8259A_irq_5,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[FLOPPY_IRQ_VECTOR],(uint32_t)__entry_8259A_irq_6,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[LPT1_IRQ_VECTOR],(uint32_t)__entry_8259A_irq_7,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[RTC_IRQ_VECTOR],(uint32_t)__entry_8259A_irq_8,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[MOUSE_IRQ_VECTOR],(uint32_t)__entry_8259A_irq_12,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[FPU_IRQ_VECTOR],(uint32_t)__entry_8259A_irq_13,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[HD_IRQ_VECTOR],(uint32_t)__entry_8259A_irq_14,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  /* systemcall */
  seg_initGate(&IDT[SYSTEM_CALL_VECTOR],(uint32_t)system_call,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  //__enableIRQ();
}

/**
 * @brief  defult irq handler for external interrupt
 * @note  not do any thing
 * @param {*}
 * @retval none
 */
void irq_defaultHandler(void)
{
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t irq_registerExtHandler(int irq, void (*handler)(void))
{
  if(ifExternIRQ(irq))
  {
    irq -= EXTERN_IRQ_START;
    ext_irq_handler_table[irq] = handler;
    return ENOERR;
  }
  return EPERM;
}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void do_pageError(uint32_t code, uint32_t addr)
{
  if(code & 0x01 != 0 )
  {
    painc("PAGE ACCESS ERROR!!!");    //！！！！权限问题引起的页错误，如果是用户进程操作此处应该强制关闭此进程
  }
  else if(code & 0x02 == 0)
  {
    painc("PAGE READ MISS!!!");  //！！！！现在还没有写时复制与换页机制，所以理论上不可能出现读取缺页
  }
  else if(addr < TASK_RETURN_HANDLER_ADDR)
  {
    painc("illegal ptr");   //！！！！！非法指针访问，同样需要关闭进程
  }
  else if(addr < PCB_BASE_ADDR)
    page_missing(addr);
  
  return;
}
