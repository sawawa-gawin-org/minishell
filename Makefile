# Parameters
NAME = <Program Name> # Fix it
DNAME = $(addsuffix _debug, $(NAME))

HEADER_DIR = ./include/
HEADERS := <Header files> # Fix it

HEADERS := $(addprefix $(HEADER_DIR), $(HEADERS))

SRC_DIR = ./src/
SRCS := <Source files from SRC_DIR> # Fix it

SRCS := $(addprefix $(SRC_DIR), $(SRCS)) 

TMP_DIR = ./tmp/
OBJ_DIR = $(addprefix $(TMP_DIR),prod/)
DOBJ_DIR = $(addprefix $(TMP_DIR),dev/)
SUB_OBJ_DIR = <Sub directries in the SRC_DIR> # Fix it

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DOBJS = $(patsubst $(SRC_DIR)%.c,$(DOBJ_DIR)%.o,$(SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = # Fix it
DFLAGS = -fdiagnostics-color=always -g3 -fsanitize=address
IFLAGS = -I$(HEADER_DIR)

# Rules

ifdef DEBUG_MODE
OBJS := $(DOBJS)
CFLAGS := $(DFLAGS)
NAME := $(DNAME)
OBJ_DIR := $(DOBJ_DIR)
endif

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(addprefix $(OBJ_DIR), $(SUB_OBJ_DIR))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

debug:
	make DEBUG_MODE=1

clean:
	rm -rf $(TMP_DIR) $(DNAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
