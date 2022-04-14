# master make file
# function: call the sub makefiles in the subfolder
# Process: 1. make the arch-irrelevant 

export DEBUG ?= 0

ifeq ($(DEBUG),1) 
CC_DBG_CFG := -g
endif
ARCH ?= x86
GCC_OPTIMIZE_LEVEL ?= 0

ifeq ($(ARCH),x86) 

else
$(error "ARCH $(ARCH) not suport")
endif

export CC := $(CROSS_COMPILE)gcc
export LD := $(CROSS_COMPILE)ld
export AS := $(CROSS_COMPILE)as
export AR := $(CROSS_COMPILE)ar
export DISASM := ndisasm

export C_FLAGS :=$(CC_DBG_CFG)  -O$(GCC_OPTIMIZE_LEVEL) -O -s  -fno-pic -fno-asynchronous-unwind-tables -m32 -fno-stack-protector
export S_FLAGS :=$(CC_DBG_CFG) -m32
export LD_FLAGS := -s --oformat binary  -m elf_i386 -o

################# color define #########################
export  DEFAULT_COLOR = "\e[0m"
export  BLACK = "\e[30;1m"
export  RED  =  "\e[31;1m"
export  GREEN = "\e[32;1m"
export YELLOW = "\e[33;1m"
export BLUE  = "\e[34;1m"
export PURPLE = "\e[35;1m"
export CYAN  = "\e[36;1m"
export WHITE = "\e[37;1m"

ARCH_DIR := arch/$(ARCH)
OBJ_DIR := $(ARCH_DIR)/output
GLOBAL_INC_DIR := include \
									include/libh \
									include/driver 

TAG_FLAG += DEBUG=$(DEBUG) \
						ARCH=$(ARCH) \
						GLOBAL_INC_DIR="$(patsubst %,../%, $(GLOBAL_INC_DIR))" \
						OBJ_DIR=../$(OBJ_DIR)


DISK_SIZE ?= 80
# make arch about code and link to output image

default:archIrrelevant 
	@echo "compile arch relevant ("$(ARCH)") source...."
	@make -C  arch/$(ARCH) $(TAG_FLAG) -s

creatDiskImage:
	@echo "create image disk image file...."
	@make -C arch/$(ARCH) creatDiskImage DISK_SIZE=$(DISK_SIZE) -s
# make codes that irrelevant from arch
archIrrelevant:
	@echo "compile commom source...."
	@make -C mm	$(TAG_FLAG) -s
	@make -C kernel	$(TAG_FLAG) -s
	@make -C fs	$(TAG_FLAG) -s
	@make -C driver	$(TAG_FLAG) -s
	@make -C server	$(TAG_FLAG) -s
	@make -C lib	$(TAG_FLAG) -s
.PHNOY:clean
clean:
	sudo make -C arch/$(ARCH) clean
	
