/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 02:18:17 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	doub_lstdelone(t_dbl_list *lst, void (*del_f)(void*))
{
	if (lst == NULL)
		return ;
	if (lst->data != NULL)
	{
		del_f(lst->data);
		lst->data = NULL;
	}
	free(lst);
	return ;
}
