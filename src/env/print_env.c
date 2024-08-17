/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:15:41 by saraki            #+#    #+#             */
/*   Updated: 2024/08/17 14:42:13 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"
#include <stdio.h>

/**
 * Prints the environment variables stored in the given linked list.
 *
 * @param env_lst The linked list containing the environment variables.
 */
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
		if (node->u_data.env_data->val != NULL)
			printf("%s=%s\n", node->u_data.env_data->key,
				node->u_data.env_data->val);
		node = node->next;
	}
	return ;
}
