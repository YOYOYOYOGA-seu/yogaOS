#include "address.h"

.code32
.global irq_default
.global timer_IRQhandler
.global keyboard_IRQhandler

// defined in irq_handler.h
irq_default:
  hlt
  jmp irq_default


/**
 * @brief  timer tick interrupt hanlder
 * @note   
 * @param {type} none
 * @retval none
 */

shced_lock:     //P-V lock
  .word 0

timer_IRQhandler:
  sub $4, %esp
  pushal
  push %ds
  push %es
  push %fs
  push %gs

  mov $SEL_GDT_GLOBAL_DATA, %ax
  mov %ax, %es
  mov %ax, %fs
  mov $0x20, %al
  out %al, $0x20 //enable other 8295A  irq

  call do_timer

__check_lock:   // P-V lock function, ensure the schedule can't be nested 
  movw shced_lock, %ax
  cmp $0, %ax 
  jne ret_irq    // if current timer_irq is in nesting, don't shedule

__schedule:

__lock:
  add $1, shced_lock

  call schedule
  cmp $0, %eax
  je ret_irq
  sub $SYS_BASE_LINEAR_ADDR, %eax
  mov %eax, %cr3

_unlock:
  sub $1, shced_lock

  jmp ret_irq


/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
 keyboard_IRQhandler:
  sub $4, %esp
  pushal
  push %ds
  push %es
  push %fs
  push %gs

  mov $0x20, %al //enable other 8295A  irq 
  out %al, $0x20

  call do_keyboard

  jmp ret_irq
/**
 * @brief  irq handler return point
 * @note  
 * @param {type} none
 * @retval none
 */
ret_irq:
  pop %gs
  pop %fs
  pop %es
  pop %ds
  popal
  add $4, %esp
  iret


