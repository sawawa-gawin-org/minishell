/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:58:13 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/27 18:26:16 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "dbllst.h"

static int	find_val(t_blst **tokens_lst, t_blst *env_lst);
static char	*strjoin_with_free(char *str1, char *str2);
static int	update_token_str(t_token_data *tok, char *str, int i, int old);

// tokenlstからVALでありHEREDOCではないトークンを探す
int	expamd_env(t_blst **tokens_lst, t_blst *env_lst)
{
	t_token_data	*data;

	data = (*tokens_lst)->data;
	while ((*tokens_lst)->data != NULL)
	{
		data = (*tokens_lst)->data;
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
	while ((*tokens_lst)->prev->data != NULL)
		*tokens_lst = (*tokens_lst)->prev;
	return (1);
}

static int	find_val(t_blst **tokens_lst, t_blst *env_lst)
{
	t_token_data	*tokendata;
	int				now_old[2];
	char			*ret;
	char			*current;

	tokendata = (*tokens_lst)->data;
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
	}
	free(tok->token_str);
	tok->token_str = new_str;
	return (1);
}
