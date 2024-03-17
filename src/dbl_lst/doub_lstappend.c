/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstappend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 01:50:48 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	doub_lstappend(t_dbl_list **head, t_dbl_list *new)
{
	t_dbl_list	*sentinel;
	t_dbl_list	*last;

	if (new == NULL)
		return ;
	sentinel = (*head)->prev;
	last = sentinel->prev;
	last->next = new;
	new->prev = last;
	new->next = sentinel;
	sentinel->prev = new;
	if ((*head)->data == NULL)
		*head = new;
	return ;
}
