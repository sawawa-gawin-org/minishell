# Hyper Parameter
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BASE_DIRNAME := $(shell basename ${MAKEFILE_DIR})
REPOSITORY_ROOT := $(abspath $(MAKEFILE_DIR)/../../)

# Parameters
LIB_NAME := libdbllst.a
HEADERS := dbllst.h
INT_HEADERS := dbllst_int.h

SRCS := doub_lstappend.c doub_lstdelall.c doub_lstdelone.c doub_lstdup.c \
	doub_lstnew.c doub_lstprepend.c doub_lstpurge.c doub_lstsearch.c

LIB_EXPORT_DIR := $(addprefix $(REPOSITORY_ROOT),/lib/)
HEADER_DIR := $(addprefix $(REPOSITORY_ROOT),/include/)

SRC_DIR := $(addprefix $(REPOSITORY_ROOT),/src/$(BASE_DIRNAME)/)

TMP_DIR := $(addprefix $(REPOSITORY_ROOT),/tmp/)
OBJ_DIR := $(addprefix $(TMP_DIR),prod/$(BASE_DIRNAME)/)
DOBJ_DIR := $(addprefix $(TMP_DIR),dev/$(BASE_DIRNAME)/)
SUB_OBJ_DIR := ./

CC := cc
CFLAGS := -Wall -Wextra -Werror
LFLAGS := 
DLFLAGS := 
DFLAGS := -fdiagnostics-color=always -g3 -fsanitize=address
IFLAGS := -I$(HEADER_DIR)

DEPENDENCY := 
DEPENDENCY_LIB := 

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

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) $(INT_HEADERS)
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
