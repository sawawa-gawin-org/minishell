/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstprepend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 02:52:34 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"

void	doub_lstprepend(t_dbl_list **head, t_dbl_list *new_node)
{
	t_dbl_list	*sentinel;

	if (new_node == NULL)
		return ;
	sentinel = (*head)->prev;
	sentinel->next = new_node;
	new_node->prev = sentinel;
	new_node->next = (*head);
	(*head)->prev = new_node;
	*head = new_node;
	return ;
}
