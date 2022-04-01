INC_DIR = $(GLOBAL_INC_DIR) \
					$(x86_INC_DIR) \


INC_DIR := $(patsubst %, -I %, $(INC_DIR))
SRC_DIR := ./ 

ARCH_OBJ_DIR = ./

LIB_FILE = libyoga.a

S_FILES := $(notdir $(foreach dir, $(SRC_DIR),$(wildcard $(dir)/*.S)))
C_FILES := $(notdir $(foreach dir, $(SRC_DIR),$(wildcard $(dir)/*.c)))

S_OBJS := $(patsubst %.S, $(ARCH_OBJ_DIR)/%.o, $(S_FILES))
C_OBJS := $(patsubst %.c, $(ARCH_OBJ_DIR)/%.o, $(C_FILES))

OBJS := $(S_OBJS) $(C_OBJS)
DEPS_ALL := $(OBJS:.o=.d)

defualt:$(OBJS)
	@echo $(PURPLE)"\tAR\t"$(DEFAULT_COLOR)"$@"
	@$(AR) crv  $(x86_OBJ_DIR)/$(LIB_FILE)  *.o
	@rm -f *.o *.d

-include $(DEPS_ALL) 
$(S_OBJS) : $(ARCH_OBJ_DIR)/%.o : %.S
	@echo $(PURPLE)"\tASM\t"$(DEFAULT_COLOR)"$@"
	@$(CC)  $(INC_DIR)  -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $< 
	@$(CC) $(S_FLAGS)   $(INC_DIR) -c -o $@ $<
# -fno-pic: don't use location Unrelated compiling mode (or it will creat relocation sector)
# -fno-asynchronous-unwind-tables: to aviod creat sector .eh_frame
$(C_OBJS) : $(ARCH_OBJ_DIR)/%.o : %.c
	@echo $(PURPLE)"\tCC\t"$(DEFAULT_COLOR)"$@"
	@$(CC)  $(INC_DIR)  -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $< 
	@$(CC) -s  -fno-pic -fno-asynchronous-unwind-tables -m32 $(INC_DIR) -c -o $@ $<
