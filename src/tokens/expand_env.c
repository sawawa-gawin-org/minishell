/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:58:13 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/06 15:23:04 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static int	find_val(t_blst **tokens_lst, t_blst *env_lst);
static int	update_token_str(t_token_data *tok, char *str, int i, int old);

// tokenlstからVALでありHEREDOCではないトークンを探す
int	expand_env(t_blst **tokens_lst, t_blst *env_lst)
{
	t_token_data	*data;

	data = (*tokens_lst)->data.t_data;
	while ((*tokens_lst)->data.t_data != NULL)
	{
		data = (*tokens_lst)->data.t_data;
		if ((data->token_type == VAL_FLAG \
			|| data->token_type == DOUBLE_QUOTE_VAL_FLAG) \
			&& (data->sub_type != HEREDOC_FLAG \
			&& data->sub_type != HEREDOC_QUOTE_FLAG))
		{
			if (!find_val(tokens_lst, env_lst))
				return (0);
		}
		*tokens_lst = (*tokens_lst)->next;
	}
	while ((*tokens_lst)->prev->data.t_data != NULL)
		*tokens_lst = (*tokens_lst)->prev;
	return (1);
}

static int	find_val(t_blst **tokens_lst, t_blst *env_lst)
{
	t_token_data	*tokendata;
	int				now_old[2];
	char			*ret;

	tokendata = (*tokens_lst)->data.t_data;
	now_old[0] = 0;
	now_old[1] = 0;
	ret = ft_calloc(1, 1);
	if (!ret)
		return (0);
	while (tokendata->token_str[now_old[0]] != '\0')
	{
		if (tokendata->token_str[now_old[0]] == '$')
		{
			ret = add_val_to_str(tokendata->token_str, ret, now_old, env_lst);
			if (!ret)
				return (0);
			now_old[0] += 1 + get_val_len(tokendata->token_str, now_old[0] + 1);
			now_old[1] = now_old[0];
		}
		else
			now_old[0] += 1;
	}
	return (update_token_str(tokendata, ret, now_old[0], now_old[1]));
}

static int	update_token_str(t_token_data *tok, char *str, int now, int old)
{
	char	*current;
	char	*new_str;

	if (tok->token_str[now] == '\0' && old < now)
	{
		current = ft_substr(tok->token_str, old, now - old);
		if (!current)
			return (0);
		new_str = strjoin_allfree(str, current);
		if (!new_str)
			return (0);
		free(tok->token_str);
		tok->token_str = ft_strdup(new_str);
		free(new_str);
	}
	else
	{
		free(tok->token_str);
		tok->token_str = ft_strdup(str);
		free(str);
	}
	if (tok->token_str == NULL)
		return (0);
	return (1);
}
