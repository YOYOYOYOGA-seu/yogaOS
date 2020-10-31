#include "address.h"
.extern  sys_call_table
.extern  numOfSystemCalls
.global system_call


/**
 * @brief  system call interrupt 
 * @note   INT 0x80
 * @param {type} none
 * @retval none
 */
system_call:
  sub $4, %esp
  pushal
  push %ds
  push %es
  push %fs
  push %gs
  push %eax
  mov $SEL_GDT_GLOBAL_DATA, %ax
  mov %ax, %es
  mov %ax, %fs
  pop %eax

  cmpl numOfSystemCalls, %eax
  jae illegal_sys_call
  push %edx
  push %ecx
  push %ebx
  sti    //open interrupt

  call *sys_call_table(,%eax,4)
  add $0xc, %esp
  
  //Save the return data to the stack
  mov %esp, %edx
  add $11*4, %edx
  mov %eax, %ss:(%edx)

__schedule:
  call schedule
  cmp $0, %eax
  je ret_syscall
  sub $SYS_BASE_LINEAR_ADDR, %eax
  mov %eax, %cr3
  jmp ret_syscall


illegal_sys_call:
  hlt
  jmp illegal_sys_call
  
ret_syscall:
  pop %gs
  pop %fs
  pop %es
  pop %ds
  popal
  add $4, %esp
  iret





