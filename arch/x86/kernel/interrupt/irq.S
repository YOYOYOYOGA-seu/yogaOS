#include "address.h"

.code32

.global fault_default
.global page_fault
.global __entry_8259A_irq_0
.global __entry_8259A_irq_1
.global __entry_8259A_irq_2
.global __entry_8259A_irq_3
.global __entry_8259A_irq_4
.global __entry_8259A_irq_5
.global __entry_8259A_irq_6
.global __entry_8259A_irq_7
.global __entry_8259A_irq_8
.global __entry_8259A_irq_9
.global __entry_8259A_irq_10
.global __entry_8259A_irq_11
.global __entry_8259A_irq_12
.global __entry_8259A_irq_13
.global __entry_8259A_irq_14
.global __entry_8259A_irq_15
.global keyboard_irq_entry

.extern irq_enableExt
.extern irq_disableExt
.extern ext_irq_handler_table

.macro ENTRY_8259A_MASTER_IRQ irq_num
  sub $4,%esp 
  pushal 
  push %ds
  push %es 
  push %fs 
  push %gs 
  mov $0x20, %al 
  out %al, $0x20  
  movl $\irq_num, %eax 
  call *ext_irq_handler_table(,%eax,4)  //do keyboard handler
  sti 
  call schedule 
  cmp $0, %eax  
  je ret_irq  
  sub $SYS_BASE_LINEAR_ADDR, %eax 
  mov %eax, %cr3  
  jmp ret_irq
.endm



fault_default:
  hlt
  jmp fault_default

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
 * @brief IRQ vector of external interrupt (8259A controller)
 * @note  
 * @param {type} none
 * @retval none
 */
__entry_8259A_irq_0:
  ENTRY_8259A_MASTER_IRQ 0

__entry_8259A_irq_1:
  ENTRY_8259A_MASTER_IRQ 1

__entry_8259A_irq_2:
  ENTRY_8259A_MASTER_IRQ 2

__entry_8259A_irq_3:
  ENTRY_8259A_MASTER_IRQ 3

__entry_8259A_irq_4:
  ENTRY_8259A_MASTER_IRQ 4

__entry_8259A_irq_5:
  ENTRY_8259A_MASTER_IRQ 5

__entry_8259A_irq_6:
  ENTRY_8259A_MASTER_IRQ 6

__entry_8259A_irq_7:
  ENTRY_8259A_MASTER_IRQ 7

__entry_8259A_irq_8:
  ENTRY_8259A_MASTER_IRQ 8

__entry_8259A_irq_9:
  ENTRY_8259A_MASTER_IRQ 9

__entry_8259A_irq_10:
  ENTRY_8259A_MASTER_IRQ 10

__entry_8259A_irq_11:
  ENTRY_8259A_MASTER_IRQ 11

__entry_8259A_irq_12:
  ENTRY_8259A_MASTER_IRQ 12

__entry_8259A_irq_13:
  ENTRY_8259A_MASTER_IRQ 13

__entry_8259A_irq_14:
  ENTRY_8259A_MASTER_IRQ 14

__entry_8259A_irq_15:
  ENTRY_8259A_MASTER_IRQ 15

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


