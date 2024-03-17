/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 01:44:25 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_dbl_list	*doub_lstnew(void *data)
{
	t_dbl_list	*new;

	new = malloc(sizeof(t_dbl_list));
	if (new == NULL)
		return (NULL);
	new->prev = new;
	new->data = data;
	new->next = new;
	return (new);
}
