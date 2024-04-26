# Library TEST Makefile

# Hyper Parameter
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BASE_DIRNAME := $(shell basename ${MAKEFILE_DIR})
REPOSITORY_ROOT := $(abspath $(MAKEFILE_DIR)/../../)

include $(REPOSITORY_ROOT)/src/$(BASE_DIRNAME)/Makefile

# Parameters
NAME := libft.out
TEST_SRCS := main.c

# *****************************************************************************
# From here onward is the same
# *****************************************************************************

DNAME := $(NAME:.out=_debug.out)

TEST_SRC_DIR := $(addprefix $(REPOSITORY_ROOT),/test/$(BASE_DIRNAME)/)

NAME := $(addprefix $(TEST_SRC_DIR),$(NAME))
DNAME := $(addprefix $(TEST_SRC_DIR),$(DNAME))

TEST_SRCS := $(addprefix $(TEST_SRC_DIR),$(TEST_SRCS)) 

TEST_OBJS := $(patsubst $(TEST_SRC_DIR)%.c,$(OBJ_DIR)%.o,$(TEST_SRCS))
TEST_DOBJS := $(patsubst $(TEST_SRC_DIR)%.c,$(DOBJ_DIR)%.o,$(TEST_SRCS))

# Rules
ifdef DEBUG_MODE
TEST_OBJS := $(TEST_DOBJS)
LFLAGS := $(DLFLAGS)
NAME := $(DNAME)
endif

# Rules
.PHONY: test
test: $(OBJ_DIR) $(DEPENDENCY) $(NAME)

$(NAME): $(OBJS) $(TEST_OBJS) $(DEPENDENCY_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_OBJS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(TEST_SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: tclean
tclean:
	rm -f $(NAME) $(DNAME)
