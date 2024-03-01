# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 19:07:05 by syamasaw          #+#    #+#              #
#    Updated: 2024/03/01 18:25:11 by saraki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Hyper Parameter
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BASE_DIRNAME := $(shell basename ${MAKEFILE_DIR})
REPOSITORY_ROOT := $(abspath $(MAKEFILE_DIR)/../../)

# Parameters
LIB_NAME := pipex.a
HEADERS := pipex.h

SRCS := find_cmd.c my_strncpy.c child_1.c child_2.c utils.c

LIB_EXPORT_DIR := $(addprefix $(REPOSITORY_ROOT),/lib/)
HEADER_DIR := $(addprefix $(REPOSITORY_ROOT),/include/)

SRC_DIR := $(addprefix $(REPOSITORY_ROOT),/src/$(BASE_DIRNAME)/)

TMP_DIR := $(addprefix $(REPOSITORY_ROOT),/tmp/)
OBJ_DIR := $(addprefix $(TMP_DIR),prod/$(BASE_DIRNAME)/)
DOBJ_DIR := $(addprefix $(TMP_DIR),dev/$(BASE_DIRNAME)/)
SUB_OBJ_DIR := ./

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L$(LIB_EXPORT_DIR) -lft
DFLAGS = -fdiagnostics-color=always -g3 -fsanitize=address
IFLAGS = -I$(HEADER_DIR)

include $(REPOSITORY_ROOT)/src/Makefile