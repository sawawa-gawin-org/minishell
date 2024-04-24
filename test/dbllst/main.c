/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:41:53 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/22 21:34:56 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	end(void)__attribute__((destructor));

void	end(void)
{
	system("leaks dbllst.out");
}
typedef struct s_node
{
	struct s_node	*prev;
	void			*data;
	struct s_node	*next;
}				t_blst;


static t_blst *make_list(char *src);


void purge_and_delete(void **head) {
    void *purge = doub_lstpurge(head);
    doub_lstdelone(purge, NULL);
}

int	main(void)
{
	t_blst		*head;
	t_blst		*node;
	// t_blst		*tmp;

	// Make list
	head = make_list("abcdefghij");
	if (head == NULL)
		return (1);
	node = head;
	while (node->data != NULL)
	{
		printf("data:%s\n", (char *)node->data);
		node = node->next;
	}
	// tmp = doub_lstpurge((void **)&head);
	// doub_lstdelone((void *)tmp, NULL);
	purge_and_delete((void **)&head);
	node = head;
	while (node->data != NULL)
	{
		printf("data:%s\n", (char *)node->data);
		node = node->next;
	}
	doub_lstdelall((void **)&head, NULL);
	return (0);
}

static t_blst *make_list(char *src)
{
	t_blst		*head;
	t_blst		*new_node;
	int			i;

	i = 0;
	head = doub_lstnew(NULL);
	while (head != NULL && i < 10)
	{
		new_node = doub_lstnew((void *)src + i);
		if (new_node == NULL)
		{
			doub_lstdelall((void **)&head, NULL);
			return (NULL);
		}
		
		doub_lstappend((void **)&head, (void *)new_node);
		i ++;
	}
	return (head);
}
