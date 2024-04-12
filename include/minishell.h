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
	OPEN_QUOTE_FLAG = 1 << 11
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
	char		*token_str;
}				t_token_data;

typedef struct s_shval_data
{
	char	*key;
	char	*val;
	int		exported;
}			t_shval_data;

//save: 変更前の属性を保存する用の構造体
//term: 現在の端末の属性を変更する用の構造体
typedef struct s_init_data
{
	struct termios		term;
	struct termios		save;
	struct sigaction	sa;
}						t_init_data;

typedef int		(*t_cmp_f)(void *, void *);

// new tokenizer
void	*new_tokenizer(char **line);
void	free_token_data(void *data);
char	*allocate_next_token(char **line, int *next_token_type);

void	*get_env_all(char **envp);
void	free_shval_data(void *data);

void	sig_handler(int signal);
void	set_signal(int signum, void handler(int), struct sigaction *sa);

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

// delete_quote.c
void	delete_quote(t_blst **tokens_lst);

#endif