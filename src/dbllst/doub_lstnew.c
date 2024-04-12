/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/04/05 04:25:43 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst_int.h"

t_blst	*doub_lstnew(void *data)
{
	t_blst	*new;

	new = malloc(sizeof(t_blst));
	if (new == NULL)
		return (NULL);
	new->prev = new;
	new->data = data;
	new->next = new;
	return (new);
}
