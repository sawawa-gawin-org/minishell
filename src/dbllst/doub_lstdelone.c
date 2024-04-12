/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/04/05 12:07:56 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst_int.h"

void	doub_lstdelone(t_blst *lst, t_del_f del_f)
{
	if (lst == NULL)
		return ;
	if (lst->data != NULL)
	{
		if (del_f != NULL)
			del_f(lst->data);
		lst->data = NULL;
	}
	free(lst);
	return ;
}
