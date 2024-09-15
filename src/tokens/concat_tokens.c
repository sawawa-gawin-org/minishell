/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:31:36 by saraki            #+#    #+#             */
/*   Updated: 2024/09/15 02:50:06 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static int		join_consecutive_token(t_blst *now, t_blst **next);
static int		is_consecutive_types(int now, int next);
static t_tokens	select_concat_type(t_tokens now, t_tokens next);

int	concat_tokens_node(t_blst **tokens_lst)
{
	t_blst			*now;
	t_blst			*next;

	now = *tokens_lst;
	while (now->u_data.token_data != NULL)
	{
		if (now->u_data.token_data->token_type == TOKEN_FLAG)
			now->u_data.token_data->token_type = VAL_FLAG;
		next = now->next;
		if (next->u_data.token_data == NULL)
			break ;
		if (is_consecutive_types(now->u_data.token_data->token_type,
				next->u_data.token_data->token_type))
		{
			if (join_consecutive_token(now, &next))
				return (ERR_ALLOCATE_MEMORY);
		}
		else
			now = now->next;
	}
	return (OK);
}

static int	join_consecutive_token(t_blst *now, t_blst **next)
{
	char	*str1;
	char	*str2;
	char	*new_str;

	str1 = now->u_data.token_data->token_str;
	str2 = (*next)->u_data.token_data->token_str;
	new_str = ft_strjoin(str1, str2);
	if (new_str == NULL)
		return (ERR_ALLOCATE_MEMORY);
	free(str1);
	now->u_data.token_data->token_str = new_str;
	now->u_data.token_data->token_type = select_concat_type(
			now->u_data.token_data->token_type,
			(*next)->u_data.token_data->token_type);
	purge_token_node(next);
	return (OK);
}

static int	is_consecutive_types(int now, int next)
{
	if ((now == TOKEN_FLAG
			|| (now >= DOUBLE_QUOTE_FLAG && now <= VAL_FLAG))
		&& (next == TOKEN_FLAG
			|| (next >= DOUBLE_QUOTE_FLAG && next <= VAL_FLAG)))
		return (1);
	return (0);
}

static t_tokens	select_concat_type(t_tokens now, t_tokens next)
{
	if (now == SINGLE_QUOTE_FLAG || next == SINGLE_QUOTE_FLAG)
		return (SINGLE_QUOTE_FLAG);
	else if (now == DOUBLE_QUOTE_FLAG || next == DOUBLE_QUOTE_FLAG
		|| now == DOUBLE_QUOTE_VAL_FLAG || next == DOUBLE_QUOTE_VAL_FLAG)
		return (SINGLE_QUOTE_FLAG);
	else
		return (DOUBLE_QUOTE_VAL_FLAG);
	return (now);
}
