CC = cc
CFLAGS = -Wall -Wextra -Werror

LIB_SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
		ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
		ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
		ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
		ft_toupper.c

LIB_BONUS_SRCS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

HEADERS_DIR = includes
PARENT_DIR = ..

LIB_HEADER = $(PARENT_DIR)/$(HEADERS_DIR)/libft.h
LIB_HEADER_DIR = $(PARENT_DIR)/$(HEADERS_DIR)

LIB_OBJS = $(LIB_SRCS:.c=.o)
LIB_BONUS_OBJS = $(LIB_BONUS_SRCS:.c=.o)

NAME = $(PARENT_DIR)/libft.a

ifdef WITH_BONUS
LIB_OBJS += $(LIB_BONUS_OBJS)
endif

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB_OBJS)
	ar rc $@ $(LIB_OBJS)

bonus: $(LIB_OBJS) $(LIB_BONUS_OBJS)
	make WITH_BONUS=1

%.o: %.c $(LIB_HEADER)
	$(CC) $(CFLAGS) -I $(LIB_HEADER_DIR) -c $< -o $@ 

clean:
	rm -f $(LIB_OBJS) && rm -f $(LIB_BONUS_OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all
