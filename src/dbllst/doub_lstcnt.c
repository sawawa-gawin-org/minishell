/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstcnt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:14:00 by saraki            #+#    #+#             */
/*   Updated: 2024/06/19 13:16:21 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst_int.h"

size_t	doub_lstcnt(t_blst *lst)
{
	size_t	cnt;

	if (lst == NULL)
		return (0);
	cnt = 0;
	while (lst->data != NULL)
	{
		cnt++;
		lst = lst->next;
	}
	return (cnt);
}
