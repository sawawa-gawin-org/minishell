/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:15:41 by saraki            #+#    #+#             */
/*   Updated: 2024/08/17 18:10:06 by saraki           ###   ########.fr       */
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
	char	*key;
	char	*val;

	if (env_lst == NULL)
		return ;
	while (env_lst->u_data.env_data != NULL)
	{
		key = env_lst->u_data.env_data->key;
		val = env_lst->u_data.env_data->val;
		if (ft_strcmp(key, "?") != 0 && val != NULL)
			printf("%s=%s\n", key, val);
		env_lst = env_lst->next;
	}
	return ;
}
