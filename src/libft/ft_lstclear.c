/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:01:16 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 17:39:24 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*now_pt;
	t_list	*next_pt;

	next_pt = NULL;
	if (lst != NULL && *lst != NULL)
	{
		now_pt = (*lst);
		next_pt = (*lst)->next;
	}
	else
		return ;
	while (1)
	{
		ft_lstdelone(now_pt, del);
		if (next_pt == NULL)
			break ;
		now_pt = next_pt;
		next_pt = next_pt->next;
	}
	*lst = NULL;
	return ;
}
