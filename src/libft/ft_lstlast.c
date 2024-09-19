/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:35:36 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 17:39:30 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*now_pt;
	t_list	*next_pt;

	if (lst == NULL)
		return (lst);
	now_pt = lst;
	next_pt = lst->next;
	while (next_pt != NULL)
	{
		now_pt = next_pt;
		next_pt = next_pt->next;
	}
	return (now_pt);
}
