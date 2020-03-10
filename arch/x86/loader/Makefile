CURRENT_LEVEL +=../
INC_DIR := $(GLOBAL_INC_DIR) \
					$(x86_INC_DIR) \
					$(x86_AS_INC_DIR)

INC_DIR := $(patsubst %, -I %, $(INC_DIR))

a.img:mbr.bin loader.bin
  ifeq ($(DEBUG),1) 
	$(DISASM) -o 0x7c00 mbr.bin >> mbr_r.asm
	$(DISASM) -o 0x0000 loader.bin >> loader_r.asm
  endif
	dd if=/dev/zero of=a.img bs=1474560 count=1
	dd if=mbr.bin of=a.img bs=512 count=1 conv=notrunc
	sudo mv a.img $(x86_IMAGE_DIR)/a.img
	rm -f *.bin *.o 

mbr.bin: mbr.o mbr.lds
	$(LD) -M --oformat binary -m elf_i386 -o mbr.bin mbr.o -T mbr.lds

loader.bin: loader.S
	$(CC) $(S_FLAGS)   $(INC_DIR) -o loader.o -c loader.S  
	$(LD) -M --oformat binary -m elf_i386 -o loader.bin loader.o -T loader.lds 
	cp loader.bin $(x86_OUTPUT_DIR)
mbr.o: mbr.s
	$(AS) --32 mbr.s -o mbr.o $(INC_DIR)

.PHNOY:clean
clean:
	# must ad '-f'(force remove),or it will return fail and 
	# shutdown the "make clean" process
	rm -f	*_r.asm *.bin *.o *.img
	
