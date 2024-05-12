/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:32:09 by saraki            #+#    #+#             */
/*   Updated: 2024/05/07 19:57:23 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_test.h"

t_blst *commandStringToList(char *cmd)
{
	t_blst	*head_node;
	t_blst	*new_node;
	int i = 0;

	head_node = doub_lstnew(NULL);
	while (head_node != NULL && cmd[i] != NULL)
	{
		new_node = doub_lstnew(cmd[i]);
		if (new_node == NULL)
		{
			doub_lstdelall((void **)&head_node, NULL);
			return (NULL);
		}
		doub_lstappend((void **)&head_node, new_node);
		i++;
	}
	return (head_node);
}

void	dealocateList(t_blst **lst)
{
	doub_lstdelall((void **)lst, NULL);
}
