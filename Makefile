# Exec Makefile
## Hyper Parameter
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BASE_DIRNAME := $(shell basename ${MAKEFILE_DIR})
REPOSITORY_ROOT := $(abspath $(MAKEFILE_DIR)/)

NAME := minishell

## Parameters
LIB_NAME := 
HEADERS := minishell.h
INT_HEADERS := 

SRCS :=

SRCS += minishell.c
SRCS += signal_util.c

LIB_EXPORT_DIR := $(addprefix $(REPOSITORY_ROOT),/lib/)
HEADER_DIR := $(addprefix $(REPOSITORY_ROOT),/include/)

SRC_DIR := $(addprefix $(REPOSITORY_ROOT),/cmd/$(BASE_DIRNAME)/)

CC := cc
CFLAGS := -Wall -Wextra -Werror
LFLAGS := -L$(LIB_EXPORT_DIR) -ltokens -lexec -lbuiltin -lenv -ldbllst -lft -lcommon -lreadline
DLFLAGS := -L$(LIB_EXPORT_DIR) -ltokens_debug -lexec_debug -lbuiltin_debug -lenv_debug -ldbllst_debug -lft_debug -lcommon_debug -lreadline
DFLAGS := -fdiagnostics-color=always -g3 -fsanitize=address
IFLAGS := -I$(HEADER_DIR)

DEPENDENCY := libft dbllst exec tokens env common builtin
DEPENDENCY_LIB := libft.a libdbllst.a libexec.a libtokens.a libenv.a libcommon.a libbuiltin.a

# *****************************************************************************
# From here onward is the same
# *****************************************************************************

SRCS := $(addprefix $(SRC_DIR),$(SRCS)) 

NAME := $(addprefix $(REPOSITORY_ROOT),/$(NAME))
DNAME := $(NAME:=_debug)

HEADERS := $(addprefix $(HEADER_DIR),$(HEADERS))
INT_HEADERS := $(addprefix $(MAKEFILE_DIR),$(INT_HEADERS))

DEPENDENCY_LIB := $(addprefix $(LIB_EXPORT_DIR),$(DEPENDENCY_LIB))
DDEPENDENCY_LIB := $(DEPENDENCY_LIB:.a=_debug.a)

# Rules
ifdef DEBUG_MODE
CFLAGS := $(DFLAGS)
LFLAGS := $(DLFLAGS)
NAME := $(DNAME)
DEPENDENCY_LIB := $(DDEPENDENCY_LIB)
endif

all: $(DEPENDENCY) $(NAME)

$(NAME): $(SRCS) $(DEPENDENCY_LIB)
	$(CC) $(CFLAGS) $(IFLAGS) $(SRCS) $(LFLAGS) -o $@

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
	rm -rf $(OBJ_DIR) $(DOBJ_DIR) $(DNAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug clean fclean re

echo:
	@echo $(SRCS) 