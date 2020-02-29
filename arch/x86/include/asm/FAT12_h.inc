BS_NAME: .ascii "YOYOYOGA" # OEM String, 必须 8 个字节
BPB_BytsPerSec: .word 512 # 每扇区字节数
BPB_SecPerClus: .byte 1 # 每簇多少扇区
BPB_RsvdSecCnt: .word 1 # Boot 记录占用多少扇区
BPB_NumFATs: .byte 2 # 共有多少 FAT 表
BPB_RootEntCnt: .word 160 # 根目录文件数最大值
BPB_TotSec16: .word 2880 # 逻辑扇区总数
BPB_Media: .byte 0xF0 # 媒体描述符
BPB_FATSz16: .word 9 # 每FAT扇区数
BPB_SecPerTrk: .word 18 # 每磁道扇区数
BPB_NumHeads: .word 2 # 磁头数(面数)
BPB_HiddSec: .long 0 # 隐藏扇区数
BPB_TotSec32: .long 0 # wTotalSectorCount为0时这个值记录扇区数
BS_DrvNum: .byte 0 # 中断 13 的驱动器号
BS_Reserved1: .byte 0 # 未使用
BS_BootSig: .byte 0x29 # 扩展引导标记 (29h)
BS_VolID: .long 0 # 卷序列号
BS_VolLab: .ascii "systemFiles"# 卷标, 必须 11 个字节
BS_FileSysType: .ascii "FAT12   " # 文件系统类型, 必须 8个字节

FILE_BLOCK_SEC_BASE =  29
ROOT_DIR_ITEM_LEN = 32
ROOT_DIR_ITEM_NAME_LEN = 3 # unit: long
ROOT_DIR_ITEM_SEC_OFFSET = 0x1A
MSG_STR_LEN = 14
