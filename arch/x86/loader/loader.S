#include "register.inc"
#include "address.h"


//System message area
//The C struct is defined at arch/x86/include/system_x86.h

__sys_data:
loadMsg:
sysMsgMemSize:
  .long 0
emptyMsg:
  .fill 256 - (emptyMsg - loadMsg)
memChkBuf:
.fill 256
secLoadBuff:
.fill 512
fat1LoadBuff:
.fill 512
memChkNumber: 
 .long 0
__empty_sys_data:
.fill 2048 - (__empty_sys_data - __sys_data)
__end_sys_data:
//GDT Map 
__gdt_start:
LABEL_GDT:
  .word 0,0,0,0
LABEL_DESC_GLOBAL_DATA:
  .word 0xffff
  .word 0
  .byte 0
  .word DA_DRW + DA_4K_MASK + DA_LIMIT_HIGH_MASK + DA_DB_MASK //DB = 1 ,stack access use eax(32bit)
  .byte 0
LABEL_DESC_GLOBAL_CODE:
  .word 0xffff
  .word 0
  .byte 0
  .word DA_DB_MASK + DA_C + DA_4K_MASK + DA_LIMIT_HIGH_MASK 
  .byte 0
__empty_desc:
.fill 2048 - (__empty_desc - __gdt_start )
__gdt_end:

__idt_start:
LABEL_IDT:
.rept 256
  .word 0
  .word 0
  .byte 0
  .byte 0
  .word 0
.endr
__idt_end:



SYSTEM_CODE_BASE = PHY_SYS_CODE_BASE_ADDR
SEC_BUFF_BASE_ADDR = secLoadBuff
FAT1_BUFF_ADDR = fat1LoadBuff

// GDT descriptor sel
selGlobalData = LABEL_DESC_GLOBAL_DATA - __gdt_start
selGlobalCode =  LABEL_DESC_GLOBAL_CODE - __gdt_start
//data length
segStackLen = SYS_STACK_SIZE
// Top of Stack
topOfCode32Stack = segStackLen - 1 
_start:
  JMP entry
# global variable
GdtLen = __gdt_end - __gdt_start
GdtPtr:
  .word GdtLen - 1
  .long 0

IdtLen = __idt_end - __idt_start
IdtPtr:
  .word IdtLen - 1
  .long 0

.include "FAT12_h.inc"
sectorToRead: .byte 0
currentSectors: .word 18
KernelFileName: .ascii "KERNEL  BIN "

# Messeage string
strMemNotEough: .ascii "The memory size is too small to boot!!!\n\r"
strInitDesc: .ascii "Initialize GDT and IDT mem poor...\n\r"
strInitPage: .ascii "Initialize kernel page map...\n\r"
strInit8259A: .ascii "Initialize 8295A...\n\r"
strNotFound: .ascii "No kernel!!!\n\r"
strFound: .ascii "loading kernel...\n\r"
strFinish: .ascii "Kernel load.\n\r"

__strEnd:
strMemNotEoughLen =strInitDesc - strMemNotEough
strInitDescLen = strInitPage - strInitDesc
strInitPageLen = strInit8259A - strInitPage
strInit8259ALen = strNotFound - strInit8259A
strFoundLen = strFinish - strFound
strFinishLen = __strEnd - strFinish
//code under real pattern(16bit)
.code16
.section .text
__label_cod16:
entry:
//section regisiter init
  movw %cs, %ax
  movw %ax, %ds
  movw %ax, %es
  movw $PHY_SYS_STACK_TOP_ADDR, %ax
  shr $4, %ax
  movw %ax, %ss
  movw $0x00,%sp
  #reset BIOS disk irq
  mov $0x00, %ah
  mov BS_DrvNum, %dl
  int $0x13

loadKernel:
  call traverseDisk
  call getKernelLocation
  call copyCode
// cheak_mem_size:

cheak_mem_size:
  mov %cs, %ax
  mov %ax, %es
  mov $0, %ebx
  mov $memChkBuf, %di
__loop1:
  mov $0xe820, %eax
  mov $20, %cx
  mov $0x0534d4150, %edx
  int $0x15
  jc  dead_loop16
  incl memChkNumber
  mov $1, %eax
  cmp memChkBuf + 4*4, %eax
  je  __addMemLength
  jmp __addMemRet

__addMemLength:
  movl memChkBuf, %eax
  add memChkBuf + 2*4, %eax
  mov %eax, sysMsgMemSize
  jmp __addMemRet

__addMemRet:
  cmp $0, %ebx
  jne __loop1
  jmp __checkMemSize

__memNotEnough:
  mov $strMemNotEough, %di
  mov $strMemNotEoughLen, %cx
  call DispString
  jmp dead_loop16

__checkMemSize:
  cmpl $MIN_SUPPRT_MEM_SIZE, sysMsgMemSize
  jb __memNotEnough


init8259A:
  mov $strInit8259A, %di
  mov $strInit8259ALen, %cx
  call DispString
  cli
  mov $0x11, %al
  out %al, $0x20  //ICW1, 8259A master
  call io_delay
  out %al, $0xA0  //ICW1, 8259A slave
  call io_delay

// irq number: 
// 8259A master: 20-27 
// 8259A slave : 28-35 
  
  mov $0x20, %al
  out %al, $0x21  //ICW2, 8259A master
  call io_delay
  mov $0x28, %al
  out %al, $0xA1  //ICW2, 8259A slave
  call io_delay

  mov  $0x04, %al
  out %al, $0x21  //ICW3, 8259A master
  call io_delay
  mov $0x02, %al
  out %al, $0xA1  //ICW3, 8259A slave
  call io_delay

  mov $0x01, %al
  out %al, $0x21  //ICW4, 8259A master
  call io_delay
  out %al, $0xA1  //ICW4, 8259A slave
  call io_delay

  mov $0xFE, %al
  out %al, $0x21  //close all 8259A master irq
  call io_delay

  mov $0xFF, %al
  out %al, $0xA1  //close all 8259A slave irq
  call io_delay

init_descriptor:
  mov $strInitDesc, %di
  mov $strInitDescLen, %cx
  call DispString
// init the gdtr regisiter 
// |    32bit    |  16bit  |
// |  base addr  |  limit  |
  
  xor %eax, %eax
  mov %ds, %ax
  shl $4, %eax
  add $LABEL_GDT, %eax
  movl %eax, (GdtPtr + 2)

  lgdt (GdtPtr)
// init the Idtr regisiter 
// |    32bit    |  16bit  |
// |  base addr  |  limit  |

  xor %eax, %eax
  mov %ds, %ax
  shl $4, %eax
  add $LABEL_IDT, %eax
  movl %eax, (IdtPtr + 2)
  cli
  lidt (IdtPtr)
// open A20 address bus
  in $0x92, %al
  or $0x02, %al
  out %al, $0x92
// init cr0 regisiter
  movl %cr0, %eax
  or $1, %eax
  mov %eax, %cr0
// jmp to 32bit code
jumpToSysCode:
  mov $selGlobalData, %ax
  mov %ax, %ss
  mov $topOfCode32Stack, %esp
  add $PHY_SYS_STACK_TOP_ADDR, %esp
  mov $selGlobalData, %ax
  mov %ax, %ds
  ljmp $selGlobalCode, $PHY_SYS_CODE_BASE_ADDR



/**
 * @brief  traverseDisk
 * @note   Traverse the image to find the kernel file
 * @param {type} none
 * @retval none
 */
traverseDisk:
  movw %cs, %ax
  mov %ax, %es
__traverseLoop:
  add $1, currentSectors
  mov $1, %cl
  mov currentSectors, %ax
  mov $SEC_BUFF_BASE_ADDR, %bx
  call readSector
  call findKernel
  cmp $1, %ax
  je foundKernel
  cmp $FILE_BLOCK_SEC_BASE, currentSectors
  jnc notfoundKernel      # exit :noot find loader
  jmp __traverseLoop

notfoundKernel:
  jmp dead_loop16
foundKernel:
  ret
/**
 * @brief  findKernel
 * @note  find if there are kernel file head in the Source folder Sector which loaded in the buff
 * @param {type} none
 * @retval %ax : $0, not found
                 $1, found
 */
findKernel:
  mov $KernelFileName, %di
  mov $0, %bx
  mov %bx, %si
  add $SEC_BUFF_BASE_ADDR, %si
  mov $ROOT_DIR_ITEM_NAME_LEN, %cl

__cmpNameLoop:
  movl %es:(%si), %eax
  cmpl (%di), %eax
  jne __nextFile
  add $4, %di
  add $4, %si
  loop __cmpNameLoop
  mov $strFound, %di
  mov $strFoundLen, %cx
  call DispString
  jmp __findInThisSec

__nextFile:
  cmp BPB_BytsPerSec, %bx
  jnc __notFindInThisSec
  add $ROOT_DIR_ITEM_LEN, %bx
  mov %bx, %si
  add $SEC_BUFF_BASE_ADDR, %si
  mov $KernelFileName, %di 
  mov $ROOT_DIR_ITEM_NAME_LEN, %cl
  jmp __cmpNameLoop

__notFindInThisSec:
  mov $0, %ax
  ret
__findInThisSec:
  mov $1, %ax
  ret

/**
 * @brief  getKernelLocation
 * @note  get the kernel file location in the image by analysis the file head and the FAT1 map
 *        then copy the kernel file to RAM
 * @param {type} none
 * @retval none
 */
 getKernelLocation:
  add $ROOT_DIR_ITEM_SEC_OFFSET - ROOT_DIR_ITEM_NAME_LEN*4, %si
  movw %es:(%si), %ax
  add $FILE_BLOCK_SEC_BASE - 2, %ax
  movw %ax,  currentSectors
  mov $1, %cl
  mov BPB_RsvdSecCnt, %ax
  mov $SEC_BUFF_BASE_ADDR, %bx
  call readSector
__transferFAT1:
  mov $FAT1_BUFF_ADDR, %ax
  mov %ax,%di
  mov $3, %si
  add $SEC_BUFF_BASE_ADDR, %si
  mov $510/2, %cx
__loopTrasFAT1:
  movw (%si), %ax
  and $0x0fff, %ax
  movw %ax, (%di)
  add $2, %di
  inc %si
  movw %es:(%si), %ax
  shr $4, %ax
  movw %ax, (%di)
  add $2, %di
  add $2, %si
  loop __loopTrasFAT1
  ret

copyCode:
  mov $PHY_SYS_CODE_BASE_ADDR, %eax
  shr $4, %eax
  mov %ax, %es
  mov $0, %bx
  mov currentSectors, %ax
  mov %ax, %di
  sub $FILE_BLOCK_SEC_BASE, %di
  shl $1, %di
__copyLoop:
  mov $1, %cl
  call readSector
  mov %gs:(%di), %ax
  cmp $0xfff, %ax
  je __finishLoad
  add BPB_BytsPerSec, %bx
  add $FILE_BLOCK_SEC_BASE - 2, %ax
  mov %ax, %di
  sub $FILE_BLOCK_SEC_BASE, %di
  shl $1, %di
  jmp __copyLoop
__finishLoad:
  mov $strFinish, %di
  mov $strFinishLen, %cx
  call DispString
  ret
/**
 * @brief  readSector
 * @note  
 *# @param  cl:    num_to_read     byte
 *         ax:    base_sector     word
 *         es:bx: buff
 * @retval none
**/
readSector:
  pushw %bp
  sub $2, %esp
  mov %sp, %bp
  movb %cl, (%bp)
  divb BPB_SecPerTrk
  inc %ah
  mov %ah, %cl
  mov %al, %ch
  mov %al, %dh
  shr $1, %ch
  and $1, %dh
  movb (%bp), %al
  mov BS_DrvNum, %dl

__reading:
  mov $0x02, %ah
  movb (%bp), %al
  int $0x13
  jc __reading    # if failed, rereading

  add $2, %esp
  popw %bp

  ret

/**
 * @brief  read disk Sector
 * @note  not used(prepear for read disk under protect mode)
 *# @param  cl:    num_to_read     byte
 *         ax:    base_sector     word
 *         es:bx: buff
 * @retval none
**/

 readSector_disk:
  push %dx
  push %di
  push %ax
  mov %bx, %di
  mov $0x1f1, %dx
  mov $0x00, %al
  out %al, %dx
  mov $0x1f2, %dx
  mov %cl, %al
  out %al, %dx

  pop %ax
  mov $0x1f3, %dx
  out %al, %dx
  inc %dx //0x1f4
  mov %ah, %al
  out %al, %dx
  inc %dx //0x1f5
  mov $0x00, %al
  out %al, %dx
  inc %dx //0x1f6
  mov $0xe0, %al
  out %al, %dx
  
  

  mov $0xf17, %dx
  mov $0x20, %al
  out %al, %dx

wait_read_complete:
  in %dx, %al
  and $0x88, %al
  cmp $0x08, %al
  jnz wait_read_complete
  
  xor %eax, %eax
  xor %ch, %ch
  mov $512, %ax
  mul %cx
  mov %ax, %cx
  mov $0x1f0, %dx
  
__reading_disk:
  
  in %dx, %ax
  mov %ax, %es:(%di)
  add $2, %di
  loop __reading_disk    # if failed, rereading

  pop %di
  pop %dx
  ret
/**
 * @brief  DispString
 * @note  
 * @param  di:  the addr of the string
 *         cx:  length
 * @retval none
**/
DispString:
  pushw %bx
__dispLoop:
  movb (%di), %al
  mov	$0x0e, %ah
  mov $0x15, %bx
  int $0x10
  inc %di
  loop __dispLoop

  popw %bx
  ret

/**
 * @brief  a dead loop under real mode, to handler fault in loading kernel
 * @note  
 * @param {type} none
 * @retval none
 */

dead_loop16:
  hlt
  jmp dead_loop16
/**
 * @brief  a delay function used in IO operation
 * @note  
 * @param {type} none
 * @retval none
 */
io_delay:
  pushw %cx
  mov $10, %cx
__nop_loop:
  nop
  loop __nop_loop
  popw %cx
  ret

__label_end_cod16:



