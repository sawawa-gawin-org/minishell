/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstpurge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 01:38:48 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_dbl_list	*doub_lstpurge(t_dbl_list **target)
{
	t_dbl_list	*next;
	t_dbl_list	*prev;
	t_dbl_list	*purged;

	if (target == NULL || *target == NULL)
		return (NULL);
	next = (*target)->next;
	prev = (*target)->prev;
	next->prev = prev;
	prev->next = next;
	(*target)->next = NULL;
	(*target)->prev = NULL;
	purged = *target;
	*target = next;
	return (purged);
}
