/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:35:20 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/24 21:08:36 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "dbllst.h"

static void	put_tokens_lst(t_blst *tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;
	int				i;

	tmp = tokens_lst;
	i = 1;
	while (tmp->data != NULL)
	{
		data = tmp->data;
		printf("%d: text:%s, type:%d, sub:%d\n", i, data->token_str, data->token_type, data->sub_type);
		tmp = tmp->next;
		i++;
	}
}

void	expand_vals(t_blst **tokens_lst, t_blst *env_lst)
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
			expand_val(tokens_lst, env_lst);
		*tokens_lst = (*tokens_lst)->next;
	}
	while ((*tokens_lst)->prev->data != NULL)
		*tokens_lst = (*tokens_lst)->prev;
}

static void	expand_val(t_blst **tokens_lst, t_blst *env_lst)
{
	t_blst			*tmp;
	t_env_data		*envdata;
	t_token_data	*tokendata;

	tmp = env_lst;
	envdata = tmp->data;
	tokendata = (*tokens_lst)->data;
	while (tmp->data != NULL)
	{
		envdata = tmp->data;
		if (ft_strcmp(tokendata->token_str, envdata->key) == 0)
		{
			overwrite();
			return ;
		}
		tmp = tmp->next;
	}
	// envになければ削除
}

int	expander(t_blst **tokens_lst, t_blst **env_lst)
{
	// 変数の展開
	
	put_tokens_lst(*tokens_lst);
	return (1);
}
