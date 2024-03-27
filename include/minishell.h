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

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

//1個のみ、シグナル番号の情報のためにグローバル変数が許可される
volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	token,
	tube,//|
	less,//<
	great,//>
	heredoc,//<<
	append,//>>
	double_quote,//""
	double_quote_val,//"$VAL"
	single_quote,//'$VAL'
	val,
	space, //' ', '\t'
	open_quote
}	t_token_type;

//双方向リスト専用構造体は廃止、置き換え予定
typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	t_token_type	token_type;
	char			*token_str;
}					t_token;

typedef struct s_shval
{
	struct s_shval	*next;
	struct s_shval	*prev;
	char			*key;
	char			*val;
	int				exported;
}					t_shval;

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			*cmd;
}					t_cmd;

//tokenizer.c
t_token	*tokenizer(char *line, t_token *tokens);
//tokenizer_util.c
int		is_token_type(char *str, int target);

//minishell.c
int		minishell(char *envp[]);

//utils.c
int		is_blank(int c);
int		is_blank_str(char *str);

//parser.c
int		syntax_checker(t_token *tokens);
int		parser(t_token **tokens, struct sigaction *sa);

//lst2way* 廃止予定
t_token	*lstadd_token(t_token *tokens, char *str, int type);
t_shval	*lstadd_shval(t_shval *shvals, char *str, int len, int flag);
void	put_lst(t_token *tokens);
void	put_lst_shval(t_shval *shvals);
void	del_lst(t_token *tokens);
void	del_lst_shval(t_shval *shvals);

//get_env_all.c
t_shval	*get_env_all(char **envp, t_shval *shvals);

//signal_utils.c
void	set_signal(int signum, void handler(int), struct sigaction *sa);
void	sig_handler(int signal);

//repl.c
int		repl(t_shval *shval, struct sigaction *sa);

//heredoc_utils.c
int		get_heredoc_fd(char *delimiter);

#endif