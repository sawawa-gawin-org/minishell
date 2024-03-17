/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:41:53 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/18 05:58:54 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"

#include <stdio.h>
#include <string.h>

// void	end(void)__attribute__((destructor));

// void	end(void)
// {
// 	system("leaks dbllst.out");
// }

typedef t_blst t_head;
typedef t_blst t_node;

static t_head *make_list(void);


int	main(void)
{
	t_head		*head;
	t_node		*node;

	// Make list
	head = make_list();
	if (head == NULL)
		return (1);
	node = head;
	while (node->data != NULL)
	{
		printf("data:%s\n", (char *)node->data);
		node = node->next;
	}
	doub_lstdelall(&head, free);
	return (0);
}

static t_head *make_list(void)
{
	t_head		*head;
	t_node		*node;
	void		*data;
	int			i;

	i = 0;
	head = doub_lstnew(NULL);
	while (head != NULL && i < 10)
	{
		data = strdup(&"abcdefghij"[i]);
		if (data == NULL)
		{
			doub_lstdelall(&head, free);
			return (NULL);
		}
		doub_lstappend(&head, node);
		i ++;
	}
	return (head);
}
