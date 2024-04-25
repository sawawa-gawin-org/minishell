/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:58:13 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/25 18:57:56 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "dbllst.h"

// 1. tokenlstからVALでありHEREDOCではないトークンを探す
void	expamd_val(t_blst **tokens_lst, t_blst *env_lst)
{
	t_token_data	*data;

	data = (*tokens_lst)->data;
	while ((*tokens_lst)->data != NULL)
	{
		data = (*tokens_lst)->data;
		if ((data->token_type == VAL_FLAG \
			|| data->token_type == DOUBLE_QUOTE_VAL_FLAG) \
			&& (data->sub_type != HEREDOC_FLAG \
			|| data->sub_type != HEREDOC_QUOTE_FLAG))
			find_val(tokens_lst, env_lst);
		*tokens_lst = (*tokens_lst)->next;
	}
	while ((*tokens_lst)->prev->data != NULL)
		*tokens_lst = (*tokens_lst)->prev;
}

static void	find_val(t_blst **tokens_lst, t_blst *env_lst)
{
	t_token_data	*tokendata;
	char			*val;
	char			*new_str;
	int				i;

	tokendata = (*tokens_lst)->data;
	i = 0;
	while (tokendata->token_str[i] != '\0')
	{
		if (tokendata->token_str[i] == '$')
		{
			i++;
			val = ft_substr(tokendata->token_str, i, get_val_len(tokendata->token_str, i));
			//一致したら値を、しなかったら空文字列を返す関数
			free(val);
		}
		i++;
	}
}

static int	get_val_len(char *str, int j)
{
	int	i = 0;

	while (str[i + j] != '\0' && str[i + j] != ' ' && str[i + j] != '$')
	{
		i++;
	}
	return (i);
}
