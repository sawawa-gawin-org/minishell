/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:29:37 by saraki            #+#    #+#             */
/*   Updated: 2024/05/01 15:37:20 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_INT_H
# define TOKENS_INT_H

typedef enum e_tokens
{
	TOKEN_FLAG = 1,
	TUBE_FLAG = 1 << 1,
	LESS_FLAG = 1 << 2,
	GREAT_FLAG = 1 << 3,
	HEREDOC_FLAG = 1 << 4,
	APPEND_FLAG = 1 << 5,
	DOUBLE_QUOTE_FLAG = 1 << 6,
	DOUBLE_QUOTE_VAL_FLAG = 1 << 7,
	SINGLE_QUOTE_FLAG = 1 << 8,
	VAL_FLAG = 1 << 9,
	SPACE_FLAG = 1 << 10,
	OPEN_QUOTE_FLAG = 1 << 11,
	HEREDOC_QUOTE_FLAG = 1 << 12,
	COMMAND_FLAG = 1 << 13
}	t_tokens;

// # define META_FLAG (LESS_FLAG | GREAT_FLAG | TUBE_FLAG | 
// 					HEREDOC_FLAG | APPEND_FLAG)
// # define QUOTE_FLAG (OPEN_QUOTE_FLAG | SINGLE_QUOTE_FLAG | 
// 					DOUBLE_QUOTE_VAL_FLAG | DOUBLE_QUOTE_FLAG)
// # define WORD_FLAG (VAL_FLAG | TOKEN_FLAG)
// # define BLANK_FLAG (SPACE_FLAG)

# define META_FLAG 62
# define QUOTE_FLAG 2496
# define WORD_FLAG 513
# define BLANK_FLAG 1024

typedef struct s_token_data
{
	t_tokens	token_type;
	t_tokens	sub_type;
	char		*token_str;
}				t_token_data;

typedef struct s_node
{
	struct s_node	*prev;
	t_token_data	*data;
	struct s_node	*next;
}				t_blst;


typedef struct s_shval_data
{
	char	*key;
	char	*val;
	int		exported;
}			t_shval_data;

typedef struct s_env_data
{
	char	*key;
	char	*val;
	int		exported;
}			t_env_data;

typedef struct s_sig
{
	int	interrupt;
}		t_sig;

typedef int		(*t_cmp_f)(void *, void *);

// tokenizer.c
void	free_token_data(void *data);
// tokenizer_util.c
char	*allocate_next_token(char **line, int *next_token_type);
int		is_val(char *str);
// heredoc_put.c
int		heredoc_put(t_blst **tokens_lst);
// heredoc_open.c
char	*heredoc_open(char *delimiter)
// heredoc_get.c
int		heredoc_get(char *delimiter)

# endif