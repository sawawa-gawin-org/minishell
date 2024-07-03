/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:15:41 by saraki            #+#    #+#             */
/*   Updated: 2024/06/26 15:56:08 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"
#include <stdio.h>

// ENVコマンドに近づけるのなら、envコマンドを実行ファイルとして作成させ、forkして実行する必要がある。
void	print_env(t_blst *env_lst)
{
	t_blst	*node;

	if (env_lst == NULL)
		return ;
	node = env_lst;
	while (node->u_data.env_data != NULL)
	{
		if (!ft_strcmp(node->u_data.env_data->key, "?"))
		{
			node = node->next;
			continue ;
		}
		printf("%s=%s\n", node->u_data.env_data->key, node->u_data.env_data->val);
		node = node->next;
	}
	return ;
}
