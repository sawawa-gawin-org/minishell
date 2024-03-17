/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstpush.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 01:46:19 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	doub_lstprepend(t_dbl_list **head, t_dbl_list *new)
{
	t_dbl_list	*sentinel;

	if (new == NULL)
		return ;
	sentinel = (*head)->prev;
	sentinel->next = new;
	new->prev = sentinel;
	new->next = (*head);
	(*head)->prev = new;
	*head = new;
	return ;
}
