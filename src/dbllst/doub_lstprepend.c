/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstprepend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/04/05 04:25:43 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst_int.h"

void	doub_lstprepend(t_blst **head, t_blst *new_node)
{
	t_blst	*sentinel;

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
