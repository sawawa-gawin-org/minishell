/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_int.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:41:20 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/29 23:17:41 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_INT_H
# define EXPANDER_INT_H

# include <stdio.h>
# include "dbllst.h"
# include "libft.h"

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

typedef struct s_env_data
{
	char	*key;
	char	*val;
	int		exported;
}			t_env_data;

// expander.c
int		expander(t_blst **tokens_lst, t_blst **env_lst);
// expand_env.c
int		expand_env(t_blst **tokens_lst, t_blst *env_lst);
// expand_util.c
char	*add_val_to_str(char *tokstr, char *str, int *now_old, t_blst *envlst);
int		get_val_len(char *str, int now);
char	*strjoin_allfree(char *str1, char *str2);

#endif