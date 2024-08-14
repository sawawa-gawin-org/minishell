/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:58:13 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/14 13:24:26 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static int	overwite_token_str(
				t_token_data *token, char *buff, int now, int old);

int	expand_env_as_str(t_token_data *tokendata, t_blst *env_lst)
{
	t_indexes		index;
	char			*buff;

	index.now = 0;
	index.old = 0;
	buff = (char *)ft_calloc(1, sizeof(char));
	if (!buff)
		return (0);
	while (tokendata->token_str[index.now] != '\0')
	{
		if (tokendata->token_str[index.now] == '$')
		{
			buff = add_val_to_str(tokendata->token_str, buff, &index, env_lst);
			if (!buff)
				return (0);
			index.now += 1 + get_val_len(tokendata->token_str, index.now + 1);
			index.old = index.now;
		}
		else
			index.now += 1;
	}
	return (overwite_token_str(tokendata, buff, index.now, index.old));
}

// Description
// - if statement:
// 	when the environment varialbes are contained in a node.
// ie) `echo "$HOME aaaaaaaa"`
// - else statement:
// 	when the only environment varialbes are contained in a
// 	node, or the last string of node.
// ie) `echo "$HOME" or echo "aaaaaaa $HOME"`
static int	overwite_token_str(
				t_token_data *token, char *buff, int now, int old)
{
	char	*current;
	char	*new_str;

	if (token->token_str[now] == '\0' && old < now)
	{
		current = ft_substr(token->token_str, old, now - old);
		if (!current)
			return (0);
		new_str = strjoin_allfree(buff, current);
		if (!new_str)
			return (0);
		free(token->token_str);
		token->token_str = new_str;
	}
	else
	{
		free(token->token_str);
		token->token_str = buff;
	}
	if (token->token_str == NULL)
		return (0);
	return (1);
}
