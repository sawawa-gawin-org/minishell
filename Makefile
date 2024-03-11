# Parameters
NAME = minishell # Fix it
DNAME = $(addsuffix _debug, $(NAME))

HEADER_DIR = ./include/
HEADERS := minishell.h # Fix it

HEADERS := $(addprefix $(HEADER_DIR), $(HEADERS))

SRC_DIR = ./src/
SRCS := main.c lst_2way.c tokenizer.c tokenizer_util.c # Fix it

SRCS := $(addprefix $(SRC_DIR), $(SRCS)) 

TMP_DIR = ./tmp/
OBJ_DIR = $(addprefix $(TMP_DIR),prod/)
DOBJ_DIR = $(addprefix $(TMP_DIR),dev/)
SUB_OBJ_DIR = obj # Fix it

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DOBJS = $(patsubst $(SRC_DIR)%.c,$(DOBJ_DIR)%.o,$(SRCS))

LIBFT = lib/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline # Fix it
DFLAGS = -fdiagnostics-color=always -g3 -fsanitize=address
IFLAGS = -I$(HEADER_DIR)

# Rules

ifdef DEBUG_MODE
OBJS := $(DOBJS)
CFLAGS := $(DFLAGS)
NAME := $(DNAME)
OBJ_DIR := $(DOBJ_DIR)
endif

all: $(OBJ_DIR) $(LIBFT) $(NAME)

$(OBJ_DIR):
	mkdir -p $(addprefix $(OBJ_DIR), $(SUB_OBJ_DIR))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LFLAGS) -o $(NAME)

$(LIBFT):
	make -C src/libft

debug:
	make DEBUG_MODE=1

clean:
	make -C src/libft clean
	rm -rf $(TMP_DIR) $(DNAME)

fclean: clean
	make -C src/libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
