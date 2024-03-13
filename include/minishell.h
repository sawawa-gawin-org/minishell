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
	open_quote
}	t_token_type;

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	t_token_type	token_type;
	char			*token_str;
}					t_token;

t_token	*tokenizer(char *line, t_token *tokens);
int		is_token_type(char *str, int target);

int		is_space(int c);

int		syntax_checker(t_token *tokens);


t_token	*lstnew_2way(t_token *tokens, char *str, int type);

//debug
void	put_lst(t_token *tokens);
void	del_lst(t_token *tokens);

#endif