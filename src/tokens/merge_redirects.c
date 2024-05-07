/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:00:28 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/07 16:48:14 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static void	scrape(t_blst **lst, int type);
static int	is_type(t_blst **lst, int type);
static void	rewrite_tok(t_blst **lst, int type);

void	merge_redirects(t_blst **tokens_lst)
{
	t_token_data	*data;

	while ((*tokens_lst)->u_data.t_data != NULL)
	{
		data = (*tokens_lst)->u_data.t_data;
		if (LESS_FLAG <= data->token_type && data->token_type <= APPEND_FLAG)
		{
			scrape(tokens_lst, data->token_type);
			continue ;
		}
		(*tokens_lst) = (*tokens_lst)->next;
	}
	while ((*tokens_lst)->prev->u_data.t_data != NULL)
		(*tokens_lst) = (*tokens_lst)->prev;
}

static void	scrape(t_blst **lst, int type)
{
	void			*purged;
	t_token_data	*data;

	data = (*lst)->u_data.t_data;
	while ((LESS_FLAG <= data->token_type \
		&& data->token_type <= APPEND_FLAG) \
		|| data->token_type == SPACE_FLAG)
	{
		purged = doub_lstpurge((void **)lst);
		doub_lstdelone((void *)purged, free_token_data);
		data = (*lst)->u_data.t_data;
	}
	type = is_type(lst, type);
	while ((*lst)->u_data.t_data != NULL)
	{
		data = (*lst)->u_data.t_data;
		if ((TUBE_FLAG <= data->token_type && data->token_type <= APPEND_FLAG) \
			|| data->token_type == SPACE_FLAG)
			break ;
		rewrite_tok(lst, type);
		*lst = (*lst)->next;
	}
}

static int	is_type(t_blst **lst, int type)
{
	t_blst			*tmp;
	t_token_data	*data;

	tmp = *lst;
	while (tmp->u_data.t_data != NULL && type == HEREDOC_FLAG)
	{
		data = tmp->u_data.t_data;
		if (DOUBLE_QUOTE_FLAG <= data->token_type \
			&& data->token_type <= SINGLE_QUOTE_FLAG)
			return (HEREDOC_QUOTE_FLAG);
		tmp = tmp->next;
	}
	return (type);
}

static void	rewrite_tok(t_blst **lst, int type)
{
	t_token_data	*data;

	data = (*lst)->u_data.t_data;
	data->sub_type = type;
}
