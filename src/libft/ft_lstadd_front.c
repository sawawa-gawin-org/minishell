/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 11:33:35 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 17:39:15 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	uintptr_t	temp_addr;

	if (new == NULL)
		return ;
	temp_addr = (uintptr_t)(*lst);
	*lst = new;
	(**lst).next = (t_list *) temp_addr;
}
