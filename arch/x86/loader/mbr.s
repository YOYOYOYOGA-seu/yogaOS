
.include "address.h"
PHY_LOADER_BASE_ADDR = 0x90000
LOADER_CODE_OFFSET = 0x1800
SEC_BUFF_BASE_ADDR = __end_mbr
FAT1_BUFF_ADDR = SEC_BUFF_BASE_ADDR + 512

# x86 stack is from high addr to low addr
.code16
__stack_base:
__start:
  jmp entry
  nop

.include "FAT12_h.inc"
# global variable

sectorToRead: .byte 0
currentSectors: .word 18
loaderName: .ascii "LOADER  BIN "
strNotFound: .ascii "No bootFile!\n\r"
strFound: .ascii "Find loader.\n\r"
strFinish: .ascii "Finish load.\n\r"

 
# @brief  entry
# @note  
# @param {type} none
# @retval none
entry:
  #section regisiter init
  movw %cs, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %ss
  movw $__stack_base,%sp
  #reset BIOS disk irq
  mov $0x00, %ah
  mov BS_DrvNum, %dl
  int $0x13
  #reset screen
  mov $0x02, %ax
  int $0x10

# @brief  traverseDisk
# @note  
# @param {type} none
# @retval none 
traverseDisk:
  movw $SEC_BUFF_BASE_ADDR, %ax
  shr $4, %ax
  movw %ax, %es
__traverseLoop:
  add $1, currentSectors
  mov $1, %cl
  mov currentSectors, %ax
  mov $0, %bx
  call  readSector
  call findLoader
  cmp $FILE_BLOCK_SEC_BASE, currentSectors
  jnc notfound      # exit :noot find loader
  jmp __traverseLoop

# @brief  findLoader
# @note   loop to find if loader.bin in the sector in the buff
# @param {type} none
# @retval none
findLoader:
  mov $loaderName, %di
  mov $0, %bx
  mov %bx, %si
  mov $ROOT_DIR_ITEM_NAME_LEN, %cl

__cmpNameLoop:
  movl %es:(%si), %eax
  cmpl (%di), %eax
  jne __nextFile
  add $4, %di
  add $4, %si
  loop __cmpNameLoop
  mov $strFound, %di
  mov $MSG_STR_LEN, %cx
  call DispString
  jmp getLoaderLocation

__nextFile:
  cmp BPB_BytsPerSec, %bx
  jnc __findLoaderExit
  add $ROOT_DIR_ITEM_LEN, %bx
  mov %bx, %si
  mov $loaderName, %di 
  mov $ROOT_DIR_ITEM_NAME_LEN, %cl
  jmp __cmpNameLoop
__findLoaderExit:
  ret

# @brief  getLoaderLocation
# @note   get the location of loader.bin's file
# @param {type} none
# @retval none
getLoaderLocation:
  add $ROOT_DIR_ITEM_SEC_OFFSET - ROOT_DIR_ITEM_NAME_LEN*4, %si
  movw %es:(%si), %ax
  add $FILE_BLOCK_SEC_BASE - 2, %ax
  movw %ax,  currentSectors
  mov $1, %cl
  mov BPB_RsvdSecCnt, %ax
  mov $0, %bx
  call readSector
__transferFAT1:
  mov $FAT1_BUFF_ADDR, %ax
  mov %ax,%di
  and $0x0f, %di
  shr $4,%ax
  mov %ax, %gs
  mov $3, %si
  mov $510/2, %cx
__loopTrasFAT1:
  movw %es:(%si), %ax
  and $0x0fff, %ax
  movw %ax, %gs:(%di)
  add $2, %di
  inc %si
  movw %es:(%si), %ax
  shr $4, %ax
  movw %ax, %gs:(%di)
  add $2, %di
  add $2, %si
  loop __loopTrasFAT1


  mov $PHY_LOADER_BASE_ADDR, %eax
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
  mov $MSG_STR_LEN, %cx
  call DispString
  jmpl $PHY_LOADER_BASE_ADDR>>4, $LOADER_CODE_OFFSET

   


  



# @brief  readSector
# @note  
# @param  cl:    num_to_read     byte
#         ax:    base_sector     word
#         es:bx: buff
# @retval none
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

# @brief  DispString
# @note  
# @param  di:  the addr of the string
#         cx:  length
# @retval none

DispString:
  pushw %ds
  pushw %bx
  mov $0, %ax 
  mov %ax, %ds
__dispLoop:
  movb (%di), %al
  mov	$0x0e, %ah
  mov $0x15, %bx
  int $0x10
  inc %di
  loop __dispLoop

  popw %bx
  popw %ds
  ret

notfound:
  jmp deadLoop
deadLoop:
  hlt
  jmp deadLoop
__end_mbr_code:
  .fill 510 - __end_mbr_code - __start
  .word 0xaa55
__end_mbr:
