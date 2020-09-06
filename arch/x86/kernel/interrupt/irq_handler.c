/*
 * @Author Shi Zhangkun
 * @Date 2020-02-20 05:11:29
 * @LastEditTime 2020-09-06 01:26:50
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
//extern void disp_string32(char *info);

extern long timeCount;
gateDesc_t * const IDT = (gateDesc_t *)IDT_BASE_ADDR;
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void initInterrupt(void)
{
  seg_initGate(&IDT[PAGE_FAULT],(uint32_t)page_fault,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[TIME_IRQ_VECTOR],(uint32_t)timer_IRQhandler,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[KEYBOARD_IRQ_VECTOR],(uint32_t)keyboard_IRQhandler,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  seg_initGate(&IDT[SYSTEM_CALL_VECTOR],(uint32_t)system_call,SEL_GDT_GLOBAL_CODE,DESC_DPL_3,DESC_TYPE_386GATE_I);
  //__enableIRQ();
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
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void do_timer(void)
{
  timeCount+= SYSTEM_TICK;
  /*  test code
  if(timeCount%1000 == 0)
    disp_string32("a\0");
    */
  sched_timeTick();
}


/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void do_keyboard(void)
{
  uint8_t data;
  data = IO_inByte(0x60);
  kb_writeBuff(data);
  if(data != 0xE0 && data != 0xE1)
  {
    //semctl();           /*注意！！！！！当后期加入IPC后，在这里发送信号量以唤醒tty服务进程
  }
  //disp_string32(key);
}