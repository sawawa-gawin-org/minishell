/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:29:37 by saraki            #+#    #+#             */
/*   Updated: 2024/05/16 18:25:51 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_INT_H
# define TOKENS_INT_H

# include "libft.h"
# include "dbllst.h"

# include <stdio.h>
# include <stddef.h>
# include <fcntl.h>
# include <sys/wait.h> // Linux
# include <sys/stat.h> // Linux

# include <errno.h>

# include <readline/readline.h>
# include <readline/history.h>

# define OK 0
# define ERR -1

extern volatile sig_atomic_t	g_signal;

typedef int	(*t_cmp_f)(void *, void *);

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
}			t_tokens;

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
}			t_token_data;

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

typedef struct s_node
{
	struct s_node	*prev;
	union
	{
		t_token_data	*t_data;
		t_env_data		*e_data;
	}	u_data;
	struct s_node	*next;
}			t_blst;

typedef struct s_indexes
{
	int		now;
	int		old;
}			t_indexes;

// init_env.c
void		free_env_data(void *data);
// tokenizer.c
void		free_token_data(void *data);
int			is_blank(int c);
// tokenizer_util.c
char		*allocate_next_token(char **line, int *next_token_type);
int			is_val(char *str);

/* parser */
// syntax_checker.c
int			syntax_checker(t_blst *lst, t_cmp_f cmp_f);
// heredoc.c
char		*parse_heredoc(t_blst **tokens_lst);
// heredoc_utils.c
char		*get_heredoc_input(char *delimiter);


int			cmp_syntax(void *d, void *n);
// delete_quote.c
void		delete_quote(t_blst **tokens_lst);
// merge_redirects.c
void		merge_redirects(t_blst **tokens_lst);
// delete_blank.c
void		delete_blank(t_blst **tokens_lst);

/* expander */
// expander.c
int			expander(t_blst **tokens_lst, t_blst **env_lst);
// expand_env.c
int			expand_env(t_blst **tokens_lst, t_blst *env_lst);
// expand_util.c
char		*add_val_to_str(
				char *tokstr, char *str, t_indexes *index, t_blst *envlst);
int			get_val_len(char *str, int now);
char		*strjoin_allfree(char *str1, char *str2);

// error_print.c
int			error_println(char *str);
int			syntax_error(char *token);

#endif