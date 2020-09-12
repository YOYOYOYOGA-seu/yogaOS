#include "address.h"

.code32
.global page_fault
.global irq_default
.global timer_IRQhandler
.global keyboard_IRQhandler
.extern shced_lock
// defined in irq_handler.h

irq_default:
  hlt
  jmp irq_default


/**
 * @brief  page_fault handler entry
 * @note  
 * @param {type} none
 * @retval none
 */
page_fault:
  pushal
  push %ds
  push %es
  push %fs
  push %gs
  mov 44(%esp), %eax   //error code
  mov %cr2, %ebx      //the linear addr where occured the missing page
  pushl %ebx
  pushl %eax
  call do_pageError
  add $8, %esp
  jmp ret_irq
/**
 * @brief  timer interrupt entry
 * @note  
 * @param {type} none
 * @retval none
 */
timer_IRQhandler:
  sub $4, %esp  //no error code
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
  sti
  

__check_lock:   // P-V lock function, ensure the schedule can't be nested 
  movw shced_lock, %ax
  cmp $0, %ax 
  jne ret_irq    // if current timer_irq is in nesting, don't shedule

__schedule:

__lock:
  add $1, shced_lock

  call do_timer
  call schedule
  cmp $0, %eax
  je ret_irq
  sub $SYS_BASE_LINEAR_ADDR, %eax
  mov %eax, %cr3

__unlock:
  sub $1, shced_lock

  jmp ret_irq


/**
 * @brief  keyboad interrupt entry
 * @note  
 * @param {type} none
 * @retval none
 */
 keyboard_IRQhandler:
  sub $4, %esp //no error code
  pushal
  push %ds
  push %es
  push %fs
  push %gs
  
   //be cause 8295A(keyboard IC) IRQ will only be triggered after read data from it's buff(operated in do_keyboard)
   //so we don't have to consider IRQ nest(the next )
              
  mov $0x20, %al //enable other 8295A  irq 
  out %al, $0x20
  call do_keyboard  //
  sti
  
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


