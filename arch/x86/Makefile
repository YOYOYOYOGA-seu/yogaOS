#x86 master make file
# function: 

# path define


x86_INC_DIR := include \
							 include/asm \
							 include/driver 
x86_IMAGE_DIR := image
x86_OUTPUT_DIR := output

x86_LOADER_DIR := loader
x86_KERNEL_DIR := kernel
x86_MM_DIR := mm
x86_LIB_DIR := lib
x86_DRIVER_DIR := driver

x86_LD_OBJ :=  $(x86_OUTPUT_DIR)/*.o  $(x86_OUTPUT_DIR)/*.a
# variable to send to the next level Makefile
TAG_FLAG += DEBUG=$(DEBUG) \
							GLOBAL_INC_DIR="$(patsubst %, ../../%, $(GLOBAL_INC_DIR))" \
							x86_IMAGE_DIR=../$(x86_IMAGE_DIR) \
							x86_OUTPUT_DIR=../$(x86_OUTPUT_DIR) \
							x86_INC_DIR="$(patsubst %, ../%, $(x86_INC_DIR))"
							
# lds file define
LDS_FILE_NAME := kernel.lds
LDS_FILE := $(LDS_FILE_NAME)
# output kernel file define
KERNEL_FILE_NAME := kernel.bin
KERNEL_FILE := $(x86_OUTPUT_DIR)/$(KERNEL_FILE_NAME)


default:
	make -C $(x86_KERNEL_DIR)	$(TAG_FLAG)
	make -C $(x86_LOADER_DIR) $(TAG_FLAG)
	make -C $(x86_MM_DIR) $(TAG_FLAG)
	make -C $(x86_LIB_DIR) $(TAG_FLAG)
	make -C $(x86_DRIVER_DIR) $(TAG_FLAG)

	$(LD) $(LD_FLAGS) $(KERNEL_FILE) $(x86_LD_OBJ) -T $(LDS_FILE)
	$(LD)  -m elf_i386 -o output/kernel_dbg.elf $(x86_LD_OBJ) -T $(LDS_FILE)
	# use creatIamge.sh to load loader.bin and kernel file to the output image
	./creatImage.sh


.PHNOY:clean
clean:
	sudo make -C $(x86_LOADER_DIR) clean
	# must ad '-f'(force remove),or it will return fail and 
	# shutdown the "make clean" process
	rm -f $(x86_IMAGE_DIR)/*.img 
	rm -f $(x86_OUTPUT_DIR)/*
	
