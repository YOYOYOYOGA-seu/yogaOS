CURRENT_LEVEL +=../
INC_DIR := $(GLOBAL_INC_DIR) \
					$(x86_INC_DIR) \


INC_DIR := $(patsubst %, -I %, $(INC_DIR))

a.img:mbr.bin loader.bin
	
  ifeq ($(DEBUG),1) 
	@$(DISASM) -o 0x7c00 mbr.bin >> mbr_r.asm
	@$(DISASM) -o 0x0000 loader.bin >> loader_r.asm
  endif
	@echo $(PURPLE)"\tDD\t"$(DEFAULT_COLOR)"$@"
	@dd if=/dev/zero of=a.img bs=1474560 count=1
	@dd if=mbr.bin of=a.img bs=512 count=1 conv=notrunc
	@sudo mv a.img $(x86_IMAGE_DIR)/a.img
	@rm -f *.bin *.o 

mbr.bin: mbr.o mbr.lds
	@echo $(PURPLE)"\tLD\t"$(DEFAULT_COLOR)"$@"
	@$(LD) -M --oformat binary -m elf_i386 -o mbr.bin mbr.o -T mbr.lds


loader.bin: loader.S
	@echo $(PURPLE)"\tLD\t"$(DEFAULT_COLOR)"$@"
	@$(CC) $(S_FLAGS)   $(INC_DIR) -o loader.o -c loader.S  
	@$(LD) -M --oformat binary -m elf_i386 -o loader.bin loader.o -T loader.lds 
	@cp loader.bin $(x86_OBJ_DIR)
mbr.o: mbr.s 
	@echo $(PURPLE)"\tASM\t"$(DEFAULT_COLOR)"$@"
	@$(AS) --32 mbr.s -o mbr.o $(INC_DIR)

.PHNOY:clean
clean:
	rm -f	*_r.asm *.bin *.o *.img *.d
	
