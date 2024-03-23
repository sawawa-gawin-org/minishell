/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:46:29 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 04:42:49 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"

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
