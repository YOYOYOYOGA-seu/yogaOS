
#include "address.h"
#include "start.h"
.include "register.inc"

.code32
.extern irq_default  // Defined in /arch/x86/kernel/irq.s
.extern initSegment  // Defined in /arch/x86/kernel/init.c
.extern resetPageDir // Defined in /arch/x86/kernel/init.c
.extern main         // Defined in /arch/x86/kernel/main.c

.global disp_string32
.global _start
.global disp_pos
.section .text
_start:
  
  mov $selGlobalData, %eax
  mov %ax, %gs
  mov %ax, %fs
  mov %ax, %es
  call initKrnelPage
  jmp __to_relocate_addr + SYS_BASE_LINEAR_ADDR
__to_relocate_addr:
  call relocate_gdtr
  call relocate_igdtr
  call relocate_stack
  call resetPageDir
  call initSegment
  mov $selVideo, %eax
  mov %ax, %gs
  
  call initIDT_defualt  
  jmp main
  
dead_loop:
  hlt
  jmp dead_loop
 /**
  * @brief  
  * @note  
  * @param {type} none
  * @retval none
  */
 // relocate the gdtr regisiter 
  // |    32bit    |  16bit  |
  // |  base addr  |  limit  |
relocate_gdtr:
  xor %eax, %eax
  mov $GDT_BASE_ADDR, %eax
  movl %eax, (GdtPtr + 2)
  lgdt (GdtPtr)
  ret
// relocate the Idtr regisiter 
// |    32bit    |  16bit  |
// |  base addr  |  limit  |
relocate_igdtr:
  xor %eax, %eax
  mov $IDT_BASE_ADDR, %eax
  movl %eax, (IdtPtr + 2)
  cli
  lidt (IdtPtr)
  ret

relocate_stack:
  mov %esp, %eax
  add $SYS_BASE_LINEAR_ADDR, %eax
  mov %eax, %esp
  ret
/**
 * @brief  init kernel-use page dirction and table
 * @note  
 * @param {type} none
 * @retval none
 */
initKrnelPage:
  movl sysMemSize, %eax
  //Judge if the sysMemSize the multiple of 4M
  and $0xffc00000,%eax    
  cmp sysMemSize, %eax  
  je __align_4M
  add $1<<22, %eax  //if not, make it 4M align 
__align_4M:
//L1 table :
  shr $22, %eax
  mov %eax, %ecx
  mov $PHY_SYS_PAGE_DIR_BASE_ADDR,%edi
  xor %eax,%eax
  mov $PHY_SYS_PAGE_TBL_BASE_ADDR|PDE_P|PDE_RW, %eax //system page can't be visted by user task
__1:
  stosl
  add $4096, %eax
  loop __1
  
 //L1 table :relocate system area
  movl sysMemSize, %eax
  shr $22, %eax
  mov %eax, %ecx
  mov $SYS_BASE_LINEAR_ADDR,%eax   //get the sys relocate addr in page dir 
  shr $20, %eax
  add  $PHY_SYS_PAGE_DIR_BASE_ADDR, %eax
  mov %eax, %edi
  xor %eax,%eax
  mov $PHY_SYS_PAGE_TBL_BASE_ADDR|PDE_P|PDE_RW, %eax  //system page can't be visted by user task
  
__2:
  stosl
  add $4096, %eax
  loop __2
//L2 table
  movl sysMemSize, %eax
  shr $12, %eax
  mov %eax, %ecx
  mov $PHY_SYS_PAGE_TBL_BASE_ADDR,%edi
  xor %eax,%eax
  mov $PTE_P|PTE_RW|PTE_G, %eax //this L2 page is relacted in high addr, all page can't be visted by user 
                                  //directly(but can be visted by using user L2 page to the phy mem it own)
__3:
  stosl
  add $4096, %eax
  loop __3

__load_reg:
  mov $PHY_SYS_PAGE_DIR_BASE_ADDR, %eax
  mov %eax, %cr3
  mov %cr0, %eax
  or $0x80000000, %eax
  mov %eax, %cr0

  ret

/**
 * @brief  init IDT
 * @note  make all IDT point to irq_default
 * @param {type} none
 * @retval none
 */
initIDT_defualt:
  pushl %edi
  mov $IDT_BASE_ADDR, %edi
  mov $256, %ecx

__loop_initIDT:
  movl $0, %eax
  movw %ax, (%edi)
  shr $16, %eax
  movw %ax, 6(%edi)
  movw %cs, 2(%edi)
  movb $DA_386I_GATE, 5(%edi)
  add $8, %edi
  loop __loop_initIDT

  popl %edi
  ret

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
disp_string32:
  pushl %ebp
  mov %esp, %ebp
  pushl %esi
  mov 8(%ebp), %esi
  push %edi
  mov disp_pos, %edi

  push %gs
  pushl %eax
  mov $selVideo, %ax
  mov %ax, %gs
  mov $0x7, %ah

__loop1:
  lodsb
  cmp $0x00, %al
  jz __loop2
  cmp $0x0a, %al
  jnz __loop3
  
  mov %edi, %eax
  mov $160, %bl
  div %bl
  and $0xff, %eax
  inc %eax
  mov $160, %bl
  mul %bl
  mov %eax, %edi
  
  jmp __loop1

__loop3:
  mov %ax, %gs:(%edi)
  add $2, %edi
  jmp __loop1

__loop2:
  mov %edi, disp_pos

  popl %eax
  pop %gs
  popl %edi
  popl %esi
  popl %ebp

  ret


//test .data segment
.data
disp_pos:
  .long (80*0 + 0)*2
abc:
  .long 0
  .long 0

GdtPtr:
  .word GDT_AREA_SIZE - 1
  .long 0

IdtPtr:
  .word IDT_AREA_SIZE - 1
  .long 0