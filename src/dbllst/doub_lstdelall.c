/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstdelall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:36:14 by saraki            #+#    #+#             */
/*   Updated: 2024/04/05 12:07:43 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst_int.h"

void	doub_lstdelall(t_blst **lst, t_del_f del_f)
{
	t_blst	*next_lst;

	if (lst == NULL || *lst == NULL)
		return ;
	if ((*lst)->data == NULL)
	{
		doub_lstdelone(*lst, del_f);
		return ;
	}
	while ((*lst)->data != NULL)
	{
		if (del_f != NULL)
			del_f((*lst)->data);
		(*lst)->data = NULL;
		next_lst = (*lst)->next;
		free(*lst);
		*lst = next_lst;
	}
	free(*lst);
	return ;
}
