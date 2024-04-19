/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:41:27 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/19 22:27:47 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

static void	process_tokens(t_blst **tmp, t_token_data *data);
static int	rewrite_token(t_blst **lst, char *str, int type);

//tokens_lstを読み込み、ヒアドキュメント記号<<を見つける。
int	heredoc_put(t_blst **tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;

	tmp = *tokens_lst;
	while (tmp->data != NULL)
	{
		data = tmp->data;
		if (data->token_type == HEREDOC_FLAG) //ヒアドキュメントの記号<<を見つけたら
			process_tokens(&tmp, data);
		if (tmp != NULL)
			tmp = tmp->next;
	}
	return (1);
}

static void	process_tokens(t_blst **tmp, t_token_data *data)
{
	t_blst	*purged;
	char	*heredoc_str;

	while (data->token_type == HEREDOC_FLAG || data->token_type == SPACE_FLAG)
	{
		purged = doub_lstpurge((void **)&(*tmp));
		doub_lstdelone(purged, free_token_data);
		data = (*tmp)->data;
	}
	if (*tmp != NULL && (*tmp)->data != NULL)
	{
		heredoc_str = heredoc_open(data->token_str);
		rewrite_token(tmp, heredoc_str, DOUBLE_QUOTE_VAL_FLAG);
	}
}

static int	rewrite_token(t_blst **lst, char *str, int type)
{
	t_token_data	*data;

	data = (*lst)->data;
	if (data->token_str)
		free(data->token_str);
	data->token_str = ft_strdup(str);
	if (!data->token_str)
		return (0);
	data->token_type = type;
	return (1);
}

//data->token_typeとheredoc_strから、"$VAL"か'VAL'か"VAL"かを判断して、FLAGを割り当てる
