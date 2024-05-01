/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:31:30 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/01 15:04:47 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INT_H
# define PARSER_INT_H

# include <stdio.h>
# include "dbllst.h"
# include "libft.h"

typedef struct s_node
{
	struct s_node	*prev;
	void			*data;
	struct s_node	*next;
}				t_blst;

typedef int		(*t_cmp_f)(void *, void *);

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

typedef struct s_token_data
{
	t_tokens	token_type;
	t_tokens	sub_type;
	char		*token_str;
}				t_token_data;

typedef struct s_env_data
{
	char	*key;
	char	*val;
	int		exported;
}			t_env_data;

// syntax_checker.c
int		syntax_checker(t_blst *lst, t_cmp_f cmp_f);
int		cmp_syntax(void *d, void *n);
// delete_quote.c
void	delete_quote(t_blst **tokens_lst);
// merge_redirects.c
void	merge_redirects(t_blst **tokens_lst);
// delete_blank.c
void	delete_blank(t_blst **tokens_lst);

void	free_token_data_tmp(void *data);

#endif