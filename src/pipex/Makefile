# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 19:07:05 by syamasaw          #+#    #+#              #
#    Updated: 2024/03/01 17:45:05 by saraki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Hyper Parameter
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BASE_DIRNAME := $(shell basename ${MAKEFILE_DIR})
REPOSITORY_ROOT := $(abspath $(MAKEFILE_DIR)/../../)

NAME = pipex

LIB_EXPORT_DIR = $(addprefix $(REPOSITORY_ROOT),/lib/)

HEADER_DIR := $(addprefix $(REPOSITORY_ROOT),/include/)
HEADERS := pipex.h
HEADERS := $(addprefix $(HEADER_DIR), $(HEADERS))

SRC_DIR = $(addprefix $(REPOSITORY_ROOT),/src/$(BASE_DIRNAME)/)
SRCS = main.c find_cmd.c my_strncpy.c child_1.c child_2.c utils.c
SRCS := $(addprefix $(SRC_DIR), $(SRCS))

TMP_DIR = $(addprefix $(REPOSITORY_ROOT),/tmp/)
OBJ_DIR = $(addprefix $(TMP_DIR),prod/$(BASE_DIRNAME)/)
DOBJ_DIR = $(addprefix $(TMP_DIR),dev/$(BASE_DIRNAME)/)
SUB_OBJ_DIR = ./

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DOBJS = $(patsubst $(SRC_DIR)%.c,$(DOBJ_DIR)%.o,$(SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L$(LIB_EXPORT_DIR) -lft
DFLAGS = -fdiagnostics-color=always -g3 -fsanitize=address
IFLAGS = -I$(HEADER_DIR)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) 
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re