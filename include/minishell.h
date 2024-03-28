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

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	t_token_type	token_type;
	char			*token_str;
}					t_token;

typedef struct s_token_data
{
	t_tokens		token_type;
	char			*token_str;
}					t_token_data;

typedef struct s_shval_data
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

int		is_blank(int c);

// tokenizer
t_token	*tokenizer(char *line, t_token *tokens);
int		is_token_type(char *str, int target);
int		check_token_type(char **str);

// new tokenizer
void	*new_tokenizer(char **line);
void	free_token_data(void *data);
char	*allocate_next_token(char **line, int *next_token_type);

t_token	*lst_last(t_token *tokens);
t_token	*lst_new(void);
t_token	*lstadd_token(t_token *tokens, char *str, int type);

// parser
int		syntax_checker(t_token *tokens);

//debug
void	put_lst(t_token *tokens);
void	del_lst(t_token *tokens);

void	*get_env_all(char **envp);
void	free_shval_data(void *data);

int		parser(t_token **tokens);

int		minishell(int argc, char *argv[], char *envp[]);

#endif