
# GDT 
# Byte|      7      |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
# desc| base:31-24  | property  |  Base:23-0      |limit1:15-0|
#
# GDT_PROPERTY
# bit |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  ||  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  ||
# desc|  G  | D/B |  0  | AVL |      lidmit2:19-16     ||  P  |    DPL    |  S  |          type         ||


DA_4K_MASK   = 0x8000
DA_DB_MASK  = 0x4000
DA_AVL_MASK = 0x1000
DA_P_MASK   = 0x0080
DA_S_MASK  =  0x0010

DA_DPL0   =   0x0000
DA_DPL1		=	  0x0020	
DA_DPL2		=	  0x0040	
DA_DPL3		=	  0x0060	

RPL0 = 0x00
RPL1 = 0x01
RPL2 = 0x02
RPL3 = 0x03

DA_DR		=	0x0090	# 存在的只读数据段类型值
DA_DRW	=	0x0092	# 存在的可读写数据段属性值
DA_A_DRW =	0x0093	# 存在的已访问可读写数据段类型值
DA_C	=		0x0098	# 存在的只执行代码段属性值
DA_CR		=	0x009A	# 存在的可执行可读代码段属性值
DA_CCO	=		0x009C	# 存在的只执行一致代码段属性值
DA_CCOR		=	0x009E	# 存在的可执行可读一致代码段属性值

DA_LDT = 0x82 # 标志为LDT描述符
DA_386TSS = 0x89
DA_CALL_GATE = 0x8C
DA_386I_GATE = 0x8E
SA_TI_MASK = 0x04

DA_LIMIT_HIGH_MASK = 0x0f00

  
# PDE
PDE_P = 0x01
PDE_RW = 0x02
PDE_US = 0x04
PDE_PWT = 0x08
PDE_PCD = 0x10
PDE_A = 0x20
PDE_PS = 0x80
PDE_G = 0x100

PTE_P = 0x01
PTE_RW = 0x02
PTE_US = 0x04
PTE_G = 0x100