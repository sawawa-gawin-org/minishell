/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstdelall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:36:14 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 03:16:27 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"

void	doub_lstdelall(t_bi_lst **lst, t_del_f del_f)
{
	t_bi_lst	*next_lst;

	if (lst == NULL || *lst == NULL)
		return ;
	while ((*lst)->data != NULL)
	{
		del_f((*lst)->data);
		(*lst)->data = NULL;
		next_lst = (*lst)->next;
		free(*lst);
		*lst = next_lst;
	}
	free(*lst);
	return ;
}
