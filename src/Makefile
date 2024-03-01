SRCS := $(addprefix $(SRC_DIR), $(SRCS)) 

DLIB_NAME := $(LIB_NAME:.a=_debug.a)
LIB_NAME := $(addprefix $(LIB_EXPORT_DIR),$(LIB_NAME))
DLIB_NAME := $(addprefix $(LIB_EXPORT_DIR),$(DLIB_NAME))

HEADERS := $(addprefix $(HEADER_DIR), $(HEADERS))

OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DOBJS := $(patsubst $(SRC_DIR)%.c,$(DOBJ_DIR)%.o,$(SRCS))

# Rules
ifdef DEBUG_MODE
OBJS := $(DOBJS)
CFLAGS := $(DFLAGS)
LIB_NAME := $(DLIB_NAME)
OBJ_DIR := $(DOBJ_DIR)
endif

all: $(OBJ_DIR) $(LIB_NAME)

$(OBJ_DIR):
	mkdir -p $(addprefix $(OBJ_DIR), $(SUB_OBJ_DIR))
	mkdir -p $(LIB_EXPORT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) -c $< -o $@

$(LIB_NAME): $(OBJS)
	ar rc $@ $(OBJS)

debug:
	make DEBUG_MODE=1

clean:
	rm -rf $(OBJ_DIR) $(DOBJ_DIR) $(DLIB_NAME)

fclean: clean
	rm -f $(LIB_NAME)

re: fclean all

.PHONY: all debug clean fclean re
