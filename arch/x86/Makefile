#x86 master make file
# function: 

# path define


x86_INC_DIR := include \
							 include/asm \
							 include/driver 
x86_IMAGE_DIR := image
x86_OBJ_DIR := output

x86_LOADER_DIR := loader
x86_KERNEL_DIR := kernel
x86_MM_DIR := mm
x86_LIB_DIR := lib
x86_DRIVER_DIR := driver


x86_LD_OBJ :=  $(x86_OBJ_DIR)/*.o  $(x86_OBJ_DIR)/*.a
# variable to send to the next level Makefile
TAG_FLAG += DEBUG=$(DEBUG) \
							GLOBAL_INC_DIR="$(patsubst %, ../../%, $(GLOBAL_INC_DIR))" \
							x86_IMAGE_DIR=../$(x86_IMAGE_DIR) \
							x86_OBJ_DIR=../$(x86_OBJ_DIR) \
							x86_INC_DIR="$(patsubst %, ../%, $(x86_INC_DIR))"
							
# lds file define
LDS_FILE_NAME := kernel.lds
LDS_FILE := $(LDS_FILE_NAME)
# output kernel file define
KERNEL_FILE_NAME := kernel.bin
KERNEL_FILE := $(x86_OBJ_DIR)/$(KERNEL_FILE_NAME)
KERNEL_DBG_FILE_NAME := $(patsubst %.bin,%_dbg.bin,$(KERNEL_FILE_NAME))
KERNEL_DBG_FILE := $(x86_OBJ_DIR)/$(KERNEL_DBG_FILE_NAME)
default:
	@make -C $(x86_KERNEL_DIR)	$(TAG_FLAG)  -s
	@make -C $(x86_LOADER_DIR) $(TAG_FLAG) -s 
	@make -C  $(x86_MM_DIR) $(TAG_FLAG) -s
	@make -C  $(x86_LIB_DIR) $(TAG_FLAG) -s
	@make -C  $(x86_DRIVER_DIR) $(TAG_FLAG) -s
	
	@echo $(PURPLE)"\tLD\t"$(DEFAULT_COLOR)$(KERNEL_FILE_NAME)
	@$(LD) $(LD_FLAGS) $(KERNEL_FILE) $(x86_LD_OBJ) -T $(LDS_FILE)
	@echo $(PURPLE)"\tLD\t"$(DEFAULT_COLOR)$(KERNEL_DBG_FILE_NAME)
	@$(LD)  -m elf_i386 -o $(KERNEL_DBG_FILE) $(x86_LD_OBJ) -T $(LDS_FILE)
# use creatIamge.sh to load loader.bin and kernel file to the output image
	@echo $(GREEN)"[image]"$(DEFAULT_COLOR)" system disk image created in "$(x86_IMAGE_DIR)
	./creatImage.sh $(x86_IMAGE_DIR) $(x86_OBJ_DIR)

creatDiskImage:
	@./creatHDimage.sh  $(DISK_SIZE)

.PHNOY:clean
clean:
	sudo make -C $(x86_LOADER_DIR) clean
	rm -f $(x86_IMAGE_DIR)/a.img 
	rm -f $(x86_OBJ_DIR)/*
	
