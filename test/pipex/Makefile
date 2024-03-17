# Library TEST Makefile

# Hyper Parameter
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BASE_DIRNAME := $(shell basename ${MAKEFILE_DIR})
REPOSITORY_ROOT := $(abspath $(MAKEFILE_DIR)/../../)

include $(REPOSITORY_ROOT)/src/$(BASE_DIRNAME)/Makefile

# Parameters
NAME := pipex.out
TEST_SRCS := main.c

include $(REPOSITORY_ROOT)/test/Makefile
