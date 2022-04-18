INC_DIR := $(GLOBAL_INC_DIR) \
					$(x86_INC_DIR) \


INC_DIR := $(patsubst %, -I %, $(INC_DIR))
SRC_DIR := ./ 

ARCH_OBJ_DIR := $(x86_OBJ_DIR)

VPATH := $(SRC_DIR) #set extern src file searching dir

S_FILES := $(notdir $(foreach dir, $(SRC_DIR),$(wildcard $(dir)/*.S)))
C_FILES := $(notdir $(foreach dir, $(SRC_DIR),$(wildcard $(dir)/*.c)))

S_OBJS := $(patsubst %.S, $(ARCH_OBJ_DIR)/%.o, $(S_FILES))
C_OBJS := $(patsubst %.c, $(ARCH_OBJ_DIR)/%.o, $(C_FILES))

OBJS := $(S_OBJS) $(C_OBJS)

defualt:$(OBJS)
	@rm -f *.o *.d
$(S_OBJS) : $(ARCH_OBJ_DIR)/%.o : %.S
	@echo $(PURPLE)"\tASM\t"$(DEFAULT_COLOR)"$@"
	@$(CC) $(S_FLAGS)   $(INC_DIR) -c -o $@ $<

$(C_OBJS) : $(ARCH_OBJ_DIR)/%.o : %.c
	@echo $(PURPLE)"\tCC\t"$(DEFAULT_COLOR)"$@"
	@$(CC) $(C_FLAGS) $(INC_DIR) -c -o $@ $<