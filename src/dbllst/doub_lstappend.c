/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstappend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/04/05 04:25:43 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst_int.h"

void	doub_lstappend(t_blst **head, t_blst *new)
{
	t_blst	*sentinel;
	t_blst	*last;

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
