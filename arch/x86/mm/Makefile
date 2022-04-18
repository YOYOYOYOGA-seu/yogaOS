INC_DIR := $(GLOBAL_INC_DIR) \
					$(x86_INC_DIR) \


INC_DIR := $(patsubst %, -I %, $(INC_DIR))
SRC_DIR := ./ \
						interrupt \
						sched

ARCH_OBJ_DIR := $(x86_OBJ_DIR)

VPATH := $(SRC_DIR) #set extern src file searching dir

S_FILES := $(notdir $(foreach dir, $(SRC_DIR),$(wildcard $(dir)/*.S)))
C_FILES := $(notdir $(foreach dir, $(SRC_DIR),$(wildcard $(dir)/*.c)))

S_OBJS := $(patsubst %.S, $(ARCH_OBJ_DIR)/%.o, $(S_FILES))
C_OBJS := $(patsubst %.c, $(ARCH_OBJ_DIR)/%.o, $(C_FILES))

OBJS := $(S_OBJS) $(C_OBJS)
DEPS_ALL := $(OBJS:.o=.d)

defualt:$(OBJS)
	@rm -f *.o *.d

-include $(DEPS_ALL) 
$(S_OBJS) : $(ARCH_OBJ_DIR)/%.o : %.S
	@echo $(PURPLE)"\tASM\t"$(DEFAULT_COLOR)"$@"
	@$(CC)  $(INC_DIR)  -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $< 
	@$(CC) $(S_FLAGS)  $(INC_DIR) -c -o $@ $<

$(C_OBJS) : $(ARCH_OBJ_DIR)/%.o : %.c
	@echo $(PURPLE)"\tCC\t"$(DEFAULT_COLOR)"$@"
	@$(CC)  $(INC_DIR)  -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $< 
	@$(CC) $(C_FLAGS)  $(INC_DIR) -c -o $@ $<
