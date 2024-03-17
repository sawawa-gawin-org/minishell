/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstpurge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 03:16:27 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"

t_bi_lst	*doub_lstpurge(t_bi_lst **target)
{
	t_bi_lst	*next;
	t_bi_lst	*prev;
	t_bi_lst	*purged;

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
