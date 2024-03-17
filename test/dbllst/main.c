/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:41:53 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/18 03:34:17 by saraki           ###   ########.fr       */
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

typedef t_bi_lst t_head;
typedef t_bi_lst t_node;

static t_head *make_list(void);


int	main(void)
{
	t_head		*head;
	t_node		*node;

	// Make list
	head = make_list();
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
	int			i;

	head = doub_lstnew(NULL);
	i = 0;
	while (i < 10)
	{
		node = doub_lstnew(strdup(&"abcdefghij"[i]));
		doub_lstappend(&head, node);
		i ++;
	}
	return (head);
}
