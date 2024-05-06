/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:35:20 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/06 15:23:33 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static void	put_tokens_lst(t_blst *tokens_lst);

int	expander(t_blst **tokens_lst, t_blst **env_lst)
{
	// 変数の展開
	if (!expand_env(tokens_lst, *env_lst))
		return (0);
	// put_env_lst(*env_lst);
	put_tokens_lst(*tokens_lst);
	return (1);
}

static void	put_tokens_lst(t_blst *tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;
	int				i;

	tmp = tokens_lst;
	i = 1;
	while (tmp->data.t_data != NULL)
	{
		data = tmp->data.t_data;
		printf("%d: text:%s, type:%d, sub:%d\n", i, data->token_str, data->token_type, data->sub_type);
		tmp = tmp->next;
		i++;
	}
}

// static void	put_env_lst(t_blst *env)
// {
// 	t_blst		*tmp;
// 	t_env_data	*data;
// 	int				i;

// 	tmp = env;
// 	i = 1;
// 	while (tmp->data != NULL)
// 	{
// 		data = tmp->data;
// 		printf("key:%s, val:%s, exported:%d\n", data->key, data->val, data->exported);
// 		tmp = tmp->next;
// 		i++;
// 	}
// }
