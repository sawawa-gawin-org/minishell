/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstdelall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:36:14 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 01:55:19 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	doub_lstdelall(t_dbl_list **lst)
{
	t_dbl_list	*next_lst;

	if (lst == NULL || *lst == NULL)
		return ;
	while ((*lst)->data != NULL)
	{
		free((*lst)->data);
		(*lst)->data = NULL;
		next_lst = (*lst)->next;
		free(*lst);
		*lst = next_lst;
	}
	free(*lst);
	return ;
}
