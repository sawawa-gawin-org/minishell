/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:05:36 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 17:39:39 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*next_pt;

	if (lst == NULL)
		return (0);
	counter = 1;
	next_pt = lst->next;
	while (next_pt != NULL)
	{
		counter += 1;
		next_pt = next_pt->next;
	}
	return (counter);
}
