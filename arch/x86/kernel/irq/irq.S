#include "address.h"
.code32
.global irq_default
.global timer_IRQhandler

.extern   sched
.extern  do_timer // defined in irq_handler.h
irq_default:
  hlt
  jmp irq_default


/**
 * @brief  timer tick interrupt hanlder
 * @note   
 * @param {type} none
 * @retval none
 */
timer_IRQhandler:
  sub $4, %esp
  pushal
  push %ds
  push %es
  push %fs
  push %gs
  push %eax
  mov $0x20, %al
  out %al, $0x20
  pop %eax
  call do_timer
__sched:
  call sched
  cmp $0, %eax
  je not_sched
  sub $SYS_BASE_LINEAR_ADDR, %eax
  mov %eax, %cr3





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