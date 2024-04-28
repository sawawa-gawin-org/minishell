/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:35:20 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/27 20:39:18 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "expander.h"
#include "minishell.h"
#include "libft.h"

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
	while (tmp->data != NULL)
	{
		data = tmp->data;
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
