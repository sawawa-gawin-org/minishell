/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:52:14 by syamasaw          #+#    #+#             */
/*   Updated: 2024/02/29 15:36:16 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dbllst.h"
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

//1個のみ、シグナル番号の情報のためにグローバル変数が許可される
extern volatile sig_atomic_t g_signal;

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

typedef struct s_node
{
	struct s_node	*prev;
	void			*data;
	struct s_node	*next;
}				t_blst;

typedef struct s_token_data
{
	t_tokens	token_type;
	t_tokens	sub_type;
	char		*token_str;
}				t_token_data;

typedef struct s_shval_data
{
	char	*key;
	char	*val;
	int		exported;
}			t_shval_data;

typedef struct s_sig
{
	int	interrupt;
}		t_sig;

typedef int		(*t_cmp_f)(void *, void *);

// new tokenizer
void	*new_tokenizer(char **line);
void	free_token_data(void *data);
char	*allocate_next_token(char **line, int *next_token_type);
int		is_val(char *str);

void	*get_env_all(char **envp);
void	free_shval_data(void *data);

int		get_heredoc_fd(char *delimiter);

int	exec_tokenslst_cmds(t_blst *tokens_lst);

// minishell.c
int		minishell(char *envp[]);
int		is_blank(int c);

// parser.c
int		parser(t_blst **tokens_lst);
// syntax_checker.c
int		syntax_checker(t_blst *lst, t_cmp_f cmp_f);
int		cmp_syntax(void *d, void *n);
// format_tokenlst.c
int		format_tokenlst(t_blst **tokens_lst);
// delete_quote.c
void	delete_quote(t_blst **tokens_lst);
// merge_redirects.c
void	merge_redirects(t_blst **tokens_lst);


// heredoc_put.c
int		heredoc_put(t_blst **tokens_lst);
// heredoc_open.c
char	*heredoc_open(char *delimiter);
// heredoc_get.c
int		heredoc_get(char *delimiter);

//signal_util.c
void	init_signal(void);
void	set_signal(int signum);
void	ign_signal(int signum);

#endif