/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:15:41 by saraki            #+#    #+#             */
/*   Updated: 2024/06/21 07:23:59 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"
# include <stdio.h>

void	print_env(t_blst *env_lst)
{
	t_blst	*node;

	if (env_lst == NULL)
		return ;
	node = env_lst;
	while (node->e_data != NULL)
	{
		if (!ft_strcmp(node->e_data->key, "?"))
		{
			node = node->next;
			continue ;
		}
		printf("%s=%s\n", node->e_data->key, node->e_data->val);
		node = node->next;
	}
	return ;
}
