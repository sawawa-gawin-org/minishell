/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:00:28 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/23 16:30:14 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

static int	scrape(t_blst **lst, int type);
static int	rewrite_tok(t_blst **lst, int type);

int	merge_redirects(t_blst **tokens_lst)
{
	t_token_data	*data;
	int				len;

	while ((*tokens_lst)->data != NULL)
	{
		len = 0;
		data = (*tokens_lst)->data;
		if (LESS_FLAG <= data->token_type && data->token_type <= APPEND_FLAG)
		{
			if (!scrape(tokens_lst, data->token_type))
				return (0);
		}
		(*tokens_lst) = (*tokens_lst)->next;
	}
	while ((*tokens_lst)->prev->data != NULL)
		(*tokens_lst) = (*tokens_lst)->prev;
	return (1);
}

static int	scrape(t_blst **lst, int type)
{
	void			*purged;
	t_token_data	*data;

	data = (*lst)->data;
	while ((LESS_FLAG <= data->token_type \
		&& data->token_type <= APPEND_FLAG) \
		|| data->token_type == SPACE_FLAG)
	{
		purged = doub_lstpurge((void **)lst);
		doub_lstdelone((void *)purged, free_token_data);
		data = (*lst)->data;
	}
	// while ((*lst)->data != NULL)
	// {
		
	// }
	
	if (*lst != NULL && (*lst)->data != NULL)
	{
		//現在のstrと、それに続く文字列すべてが対象になる
		//<< EOF""EOFの場合、変数展開が起こらない
		
		if (DOUBLE_QUOTE_FLAG <= data->token_type \
			&& data->token_type <= SINGLE_QUOTE_FLAG)
			if (type == HEREDOC_FLAG)
				type = HEREDOC_QUOTE_FLAG;
		if (!rewrite_tok(lst, type))
			return (0);
	}
	return (1);
}

// static int	is_type(t_blst *lst)
// {
// 	t_blst			*tmp;
// 	t_token_data	*data;
// 	int				type;

// 	tmp = lst;
// 	type = 0;
// 	data = tmp->data;
// 	while (tmp->data != NULL)
// 	{
// 		data = tmp->data;
// 		printf("text:%s, type:%d\n", data->token_str, data->token_type);
// 		tmp = tmp->next;
// 	}
// }

static int	rewrite_tok(t_blst **lst, int type)
{
	t_token_data	*data;

	data = (*lst)->data;
	data->token_type = type;
	return (1);
}
