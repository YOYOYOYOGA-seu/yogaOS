# master make file
# function: call the sub makefiles in the subfolder
# Process: 1. make the arch-irrelevant 

export DEBUG ?= 0

ifeq ($(DEBUG),1) 
CC_DBG_CFG := -g
endif

ARCH ?= x86
export CC := $(CROSS_COMPILE)gcc
export LD := $(CROSS_COMPILE)ld
export AS := $(CROSS_COMPILE)as
export AR := $(CROSS_COMPILE)ar
export DISASM := ndisasm

export C_FLAGS :=$(CC_DBG_CFG) -s  -fno-pic -fno-asynchronous-unwind-tables -m32 -fno-stack-protector
export S_FLAGS :=$(CC_DBG_CFG) -m32
export LD_FLAGS := -s --oformat binary  -m elf_i386 -o
ARCH_DIR := arch/$(ARCH)
OUTPUT_DIR := $(ARCH_DIR)/output
GLOBAL_INC_DIR := include 


TAG_FLAG += DEBUG=$(DEBUG) \
						ARCH=$(ARCH) \
						GLOBAL_INC_DIR=../$(GLOBAL_INC_DIR) \
						OUTPUT_DIR=../$(OUTPUT_DIR)


# make arch about code and link to output image

default:archIrrelevant
	make -C arch/$(ARCH) $(TAG_FLAG)
	
# make codes that irrelevant from arch
archIrrelevant:
	make -C mm	$(TAG_FLAG)
	make -C kernel	$(TAG_FLAG)
	make -C lib	$(TAG_FLAG)
.PHNOY:clean
clean:
	sudo make -C arch/$(ARCH) clean
	
