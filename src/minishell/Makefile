# Hyper Parameter
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BASE_DIRNAME := $(shell basename ${MAKEFILE_DIR})
REPOSITORY_ROOT := $(abspath $(MAKEFILE_DIR)/../../)

# Parameters
LIB_NAME := libminishell.a
HEADERS := minishell.h
INT_HEADERS :=

SRCS := minishell.c signal_util.c parser.c syntax_checker.c \
		get_env_all.c tokenizer.c tokenizer_util.c delete_quote.c exec_bridge.c \
		delete_blank.c merge_redirects.c

LIB_EXPORT_DIR := $(addprefix $(REPOSITORY_ROOT),/lib/)
HEADER_DIR := $(addprefix $(REPOSITORY_ROOT),/include/)

SRC_DIR := $(addprefix $(REPOSITORY_ROOT),/src/$(BASE_DIRNAME)/)

TMP_DIR := $(addprefix $(REPOSITORY_ROOT),/tmp/)
OBJ_DIR := $(addprefix $(TMP_DIR),prod/$(BASE_DIRNAME)/)
DOBJ_DIR := $(addprefix $(TMP_DIR),dev/$(BASE_DIRNAME)/)
SUB_OBJ_DIR := ./

CC := cc
CFLAGS := -Wall -Wextra -Werror
LFLAGS := -L$(LIB_EXPORT_DIR) -lexec -ldbllst -lft -lreadline
DLFLAGS := -L$(LIB_EXPORT_DIR) -lexec_debug -ldbllst_debug -lft_debug -lreadline
DFLAGS := -fdiagnostics-color=always -g3 -fsanitize=address
IFLAGS := -I$(HEADER_DIR)

DEPENDENCY := libft dbllst exec
DEPENDENCY_LIB := libft.a libdbllst.a libexec.a

# *****************************************************************************
# From here onward is the same
# *****************************************************************************

SRCS := $(addprefix $(SRC_DIR), $(SRCS)) 

DLIB_NAME := $(LIB_NAME:.a=_debug.a)
LIB_NAME := $(addprefix $(LIB_EXPORT_DIR),$(LIB_NAME))
DLIB_NAME := $(addprefix $(LIB_EXPORT_DIR),$(DLIB_NAME))

HEADERS := $(addprefix $(HEADER_DIR), $(HEADERS))
INT_HEADERS := $(addprefix $(MAKEFILE_DIR),$(INT_HEADERS))

OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DOBJS := $(patsubst $(SRC_DIR)%.c,$(DOBJ_DIR)%.o,$(SRCS))

DEPENDENCY_LIB := $(addprefix $(LIB_EXPORT_DIR),$(DEPENDENCY_LIB))
DDEPENDENCY_LIB := $(DEPENDENCY_LIB:.a=_debug.a)

# Rules
ifdef DEBUG_MODE
OBJS := $(DOBJS)
CFLAGS := $(DFLAGS)
LIB_NAME := $(DLIB_NAME)
OBJ_DIR := $(DOBJ_DIR)
DEPENDENCY_LIB := $(DDEPENDENCY_LIB)
endif

all: $(OBJ_DIR) $(DEPENDENCY) $(LIB_NAME)

$(OBJ_DIR):
	mkdir -p $(addprefix $(OBJ_DIR), $(SUB_OBJ_DIR))
	mkdir -p $(LIB_EXPORT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIB_NAME): $(OBJS)
	ar rc $@ $(OBJS)

define LIB_MACRO
.PHONY: $(1)
$(1):
	make -C $(addprefix $(REPOSITORY_ROOT),/src/$(1)) 
$(1)_clean:
	make -C $(addprefix $(REPOSITORY_ROOT),/src/$(1)) fclean
endef
$(foreach lib,$(DEPENDENCY),$(eval $(call LIB_MACRO,$(lib))))

debug:
	make DEBUG_MODE=1

clean: $(DEPENDENCY:=_clean)
	rm -rf $(OBJ_DIR) $(DOBJ_DIR) $(DLIB_NAME)

fclean: clean
	rm -f $(LIB_NAME)

re: fclean all

.PHONY: all debug clean fclean re
