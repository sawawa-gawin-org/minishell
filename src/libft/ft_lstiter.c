/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 07:13:48 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 17:39:28 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*now_pt;
	t_list	*next_pt;

	if (f == NULL || lst == NULL)
		return ;
	now_pt = lst;
	next_pt = lst->next;
	while (next_pt != NULL)
	{
		f(now_pt->content);
		now_pt = next_pt;
		next_pt = next_pt->next;
	}
	f(now_pt->content);
	return ;
}
