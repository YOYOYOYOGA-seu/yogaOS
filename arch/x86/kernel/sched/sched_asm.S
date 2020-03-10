#include "address.h"
.global task_copyRetHandler
.global task_retHandler
.extern sleep
task_retHandler:
  jmp __handler
__handler:
  mov $1000, %eax
  push %eax
  mov $sleep, %esi    
  //becasue of this func have to copy to another address ,
  //so must use Absolute jump, can't use "call sleep"(Relative to jump)
  call %esi       
  add $4, %esp
  jmp task_retHandler
__end_retHandler:

task_retHandler_length = __end_retHandler - task_retHandler  //the length of retHandler

task_copyRetHandler:   //void task_copyRetHandler(void * retFuncPage)
  
  push %ecx
  push %esi
  push %edi
  push %ds
  push %es
  push %eax
  mov $SEL_GDT_GLOBAL_DATA,%ax
  mov %ax, %ds
  mov %ax, %es
  mov 28(%esp), %edi    
  mov $task_retHandler, %esi  

  mov $task_retHandler_length, %ecx
__loop_copy:  
  movsb
  loop __loop_copy

  pop %eax
  pop %es
  pop %ds
  pop %edi
  pop %esi
  pop %ecx

  ret