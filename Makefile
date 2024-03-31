# ippatu Makefile

NAME = minishell
DNAME = $(addsuffix _debug, $(NAME))

HEADER_DIR = ./include/
HEADERS := minishell.h libft.h dbllst.h

HEADERS := $(addprefix $(HEADER_DIR), $(HEADERS))

SRC_DIR = ./src/
SRCS := main.c tokenizer.c tokenizer_util.c syntax_checker.c \
		get_env_all.c signal_util.c minishell.c parser.c

SRCS := $(addprefix $(SRC_DIR), $(SRCS)) 

TMP_DIR = ./tmp/
OBJ_DIR = $(addprefix $(TMP_DIR),prod/)
DOBJ_DIR = $(addprefix $(TMP_DIR),dev/)
SUB_OBJ_DIR = obj

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DOBJS = $(patsubst $(SRC_DIR)%.c,$(DOBJ_DIR)%.o,$(SRCS))

LIBFT = lib/libft.a
DBL = lib/libdbllst.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
DFLAGS = -fdiagnostics-color=always -g3 -fsanitize=address
IFLAGS = -I$(HEADER_DIR)

# Rules

ifdef DEBUG_MODE
OBJS := $(DOBJS)
CFLAGS := $(DFLAGS)
NAME := $(DNAME)
OBJ_DIR := $(DOBJ_DIR)
endif

all: $(OBJ_DIR) $(LIBFT) $(DBL) $(NAME)

$(OBJ_DIR):
	mkdir -p $(addprefix $(OBJ_DIR), $(SUB_OBJ_DIR))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(DBL)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(DBL) $(LFLAGS) -o $(NAME)

$(LIBFT):
	make -C src/libft

$(DBL):
	make -C src/dbllst

debug:
	make DEBUG_MODE=1

clean:
	make -C src/libft clean
	make -C src/dbllst clean
	rm -rf $(TMP_DIR) $(DNAME)

fclean: clean
	make -C src/libft fclean
	make -C src/dbllst fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug clean fclean re