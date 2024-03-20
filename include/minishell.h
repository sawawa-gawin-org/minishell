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

typedef struct		s_token_data
{
	t_token_type	token_type;
	char			*token_str;
}					t_token_data;

typedef struct	s_shval_data
{
	char			*key;
	char			*val;
	int				exported;
}				t_shval_data;

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

void	free_token_data(void *data);

t_token	*lstadd_token(t_token *tokens, char *str, int type);

//debug
void	put_lst(t_token *tokens);
void	del_lst(t_token *tokens);

void	*get_env_all(char **envp);
void	free_shval_data(void *data);

int	parser(t_token **tokens);

int	minishell(int argc, char *argv[], char *envp[]);

#endif