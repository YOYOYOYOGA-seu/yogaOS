INC_DIR := $(GLOBAL_INC_DIR) \
					$(x86_INC_DIR) \


INC_DIR := $(patsubst %, -I %, $(INC_DIR))
SRC_DIR := ./ \
						char \
						block

OBJ_DIR = $(x86_OUTPUT_DIR)

VPATH := $(SRC_DIR) #set extern src file searching dir

S_FILES := $(notdir $(foreach dir, $(SRC_DIR),$(wildcard $(dir)/*.S)))
C_FILES := $(notdir $(foreach dir, $(SRC_DIR),$(wildcard $(dir)/*.c)))

S_OBJS := $(patsubst %.S, $(OBJ_DIR)/%.o, $(S_FILES))
C_OBJS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(C_FILES))

OBJS := $(S_OBJS) $(C_OBJS)

defualt:$(OBJS)
	rm -f *.o
$(S_OBJS) : $(OBJ_DIR)/%.o : %.S
	$(CC) $(S_FLAGS)   $(INC_DIR) -c -o $@ $<
	# -fno-pic: don't use location Unrelated compiling mode (or it will creat relocation sector)
	# -fno-asynchronous-unwind-tables: to aviod creat sector .eh_frame
$(C_OBJS) : $(OBJ_DIR)/%.o : %.c
	$(CC) $(C_FLAGS) $(INC_DIR) -c -o $@ $<
