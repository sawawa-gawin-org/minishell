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

t_token	*tokenizer(char *line, t_token *tokens);
int		is_token_type(char *str, int target);

int		is_blank(int c);

int		syntax_checker(t_token *tokens);


t_token	*lstadd_token(t_token *tokens, char *str, int type);

//debug
void	put_lst(t_token *tokens);
void	del_lst(t_token *tokens);

t_shval	*get_env_all(char **envp, t_shval *shvals);
t_shval	*lstadd_shval(t_shval *shvals, char *str, int len, int flag);
void	del_lst_shval(t_shval *shvals);
void	put_lst_shval(t_shval *shvals);

int	parser(t_token **tokens);

int	minishell(int argc, char *argv[], char *envp[]);

#endif