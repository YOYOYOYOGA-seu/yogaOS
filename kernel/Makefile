INC_DIR := $(GLOBAL_INC_DIR) \

INC_DIR := $(patsubst %, -I %, $(INC_DIR))

SRC_DIR := ./ \
					 sched \
					 mm

OBJ_DIR := $(OBJ_DIR)

VPATH := $(SRC_DIR) #set extern src file searching dir

C_FILES := $(notdir $(foreach dir, $(SRC_DIR),$(wildcard $(dir)/*.c)))

C_OBJS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(C_FILES))

OBJS := $(C_OBJS)
DEPS_ALL := $(OBJS:.o=.d)

defualt:$(OBJS)
	@rm -f *.o *.d

-include $(DEPS_ALL) 
$(C_OBJS) : $(OBJ_DIR)/%.o : %.c
	@echo $(PURPLE)"\tCC\t"$(DEFAULT_COLOR)"$@"
	@$(CC)  $(INC_DIR)  -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $< 
	@$(CC) $(C_FLAGS) $(INC_DIR) -c -o $@ $<
