INC_DIR := $(GLOBAL_INC_DIR) \

INC_DIR := $(patsubst %, -I %, $(INC_DIR))

SRC_DIR := ./ \
					 sched \
					 mm

OBJ_DIR = $(OUTPUT_DIR)

VPATH := $(SRC_DIR) #set extern src file searching dir

C_FILES := $(notdir $(foreach dir, $(SRC_DIR),$(wildcard $(dir)/*.c)))

C_OBJS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(C_FILES))

OBJS := $(C_OBJS)

defualt:$(OBJS)
	rm -f *.o
	# -fno-pic: don't use location Unrelated compiling mode (or it will creat relocation sector)
	# -fno-asynchronous-unwind-tables: to aviod creat sector .eh_frame
$(C_OBJS) : $(OBJ_DIR)/%.o : %.c
	$(CC) $(C_FLAGS) $(INC_DIR) -c -o $@ $<
