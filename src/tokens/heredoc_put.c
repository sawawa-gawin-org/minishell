/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:41:27 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/07 16:48:14 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static int	process_tokens(t_blst **tmp, t_token_data *data);
static int	rewrite_tok(t_blst **lst, char *str, int type);
static int	is_flag(char *heredoc_str, int type);

//tokens_lstを読み込み、ヒアドキュメント記号<<を見つける。
int	heredoc_put(t_blst **tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;

	tmp = *tokens_lst;
	while (tmp->u_data.t_data != NULL)
	{
		data = tmp->u_data.t_data;
		if (data->token_type == HEREDOC_FLAG)
		{
			if (!process_tokens(&tmp, data))
				return (0);
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
	return (1);
}

static int	process_tokens(t_blst **tmp, t_token_data *data)
{
	t_blst	*purged;
	char	*heredoc_str;
	int		flag;

	while (data->token_type == HEREDOC_FLAG || data->token_type == SPACE_FLAG)
	{
		purged = doub_lstpurge((void **)&(*tmp));
		doub_lstdelone(purged, free_token_data);
		data = (*tmp)->u_data.t_data;
	}
	if (*tmp != NULL && (*tmp)->u_data.t_data != NULL)
	{
		flag = 0;
		heredoc_str = heredoc_open(data->token_str);
		flag = is_flag(heredoc_str, data->token_type);
		if (!rewrite_tok(tmp, heredoc_str, flag))
			return (0);
	}
	return (1);
}

static int	rewrite_tok(t_blst **lst, char *str, int type)
{
	t_token_data	*data;

	data = (*lst)->u_data.t_data;
	if (data->token_str)
		free(data->token_str);
	data->token_str = ft_strdup(str);
	if (!data->token_str)
		return (0);
	data->token_type = type;
	return (1);
}

//data->token_typeとheredoc_strから、"$VAL"か'VAL'か"VAL"かを判断して、FLAGを割り当てる
static int	is_flag(char *heredoc_str, int type)
{
	if (type == SINGLE_QUOTE_FLAG)
		return (SINGLE_QUOTE_FLAG);
	else
	{
		if (is_val(heredoc_str))
			return (DOUBLE_QUOTE_VAL_FLAG);
		else
			return (DOUBLE_QUOTE_FLAG);
	}
}
