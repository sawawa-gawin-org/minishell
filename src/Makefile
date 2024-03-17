
# Hyper Parameter
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BASE_DIRNAME := $(shell basename ${MAKEFILE_DIR})
REPOSITORY_ROOT := $(abspath $(MAKEFILE_DIR)/../)

# Parameters
LIB_NAME := minishell.a
HEADERS := minishell.h

SRCS := minishell.c lst2way_token.c tokenizer.c tokenizer_util.c parser.c \
		lst2way_shval.c get_env_all.c

LIB_EXPORT_DIR := $(addprefix $(REPOSITORY_ROOT),/lib/)
HEADER_DIR := $(addprefix $(REPOSITORY_ROOT),/include/)

SRC_DIR := $(addprefix $(REPOSITORY_ROOT),/src/)

TMP_DIR := $(addprefix $(REPOSITORY_ROOT),/tmp/)
OBJ_DIR := $(addprefix $(TMP_DIR),prod/)
DOBJ_DIR := $(addprefix $(TMP_DIR),dev/)
SUB_OBJ_DIR := ./

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline -L$(LIB_EXPORT_DIR) -lft -L$(LIB_EXPORT_DIR) -ldbllst
DFLAGS = -fdiagnostics-color=always -g3 -fsanitize=address
IFLAGS = -I$(HEADER_DIR)

# *****************************************************************************
# From here onward is the same
# *****************************************************************************

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
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

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
