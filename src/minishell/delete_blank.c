/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_blank.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:59:46 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/23 14:28:14 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

static int	merge_redirects(t_blst **tokens_lst);
static int	scrape(t_blst **lst, int type);
static int	rewrite_tok(t_blst **lst, int type);

int	delete_blank(t_blst **tokens_lst)
{
	if (!merge_redirects(tokens_lst))
		return (0);
	return (1);
}

static int	merge_redirects(t_blst **tokens_lst)
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
	while ((LESS_FLAG <= data->token_type && data->token_type <= APPEND_FLAG) || data->token_type == SPACE_FLAG)
	{
		purged = doub_lstpurge((void **)lst);
		doub_lstdelone((void *)purged, free_token_data);
		data = (*lst)->data;
	}
	if (*lst != NULL && (*lst)->data != NULL)
	{
		if (DOUBLE_QUOTE_FLAG <= data->token_type && data->token_type <= SINGLE_QUOTE_FLAG)
			if (type == HEREDOC_FLAG)
				type = HEREDOC_QUOTE_FLAG;
		if (!rewrite_tok(lst, type))
			return (0);
	}
	return (1);
}

static int	rewrite_tok(t_blst **lst, int type)
{
	t_token_data	*data;

	data = (*lst)->data;
	data->token_type = type;
	return (1);
}
