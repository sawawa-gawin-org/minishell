/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstpurge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/04/05 04:25:43 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst_int.h"

t_blst	*doub_lstpurge(t_blst **target)
{
	t_blst	*next;
	t_blst	*prev;
	t_blst	*purged;

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
