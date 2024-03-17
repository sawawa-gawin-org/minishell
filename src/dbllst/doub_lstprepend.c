/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstprepend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 03:16:27 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"

void	doub_lstprepend(t_bi_lst **head, t_bi_lst *new_node)
{
	t_bi_lst	*sentinel;

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
