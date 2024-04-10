/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:19:46 by saraki            #+#    #+#             */
/*   Updated: 2024/04/05 04:25:43 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst_int.h"

t_blst	*doub_lstdup(t_blst *src, t_dup_f dup_f, t_del_f del_f)
{
	t_blst	*duped;
	t_blst	*new;
	void	*value;

	duped = doub_lstnew(NULL);
	if (duped == NULL)
		return (NULL);
	while (src->data != NULL)
	{
		value = dup_f(src->data);
		if (!value)
		{
			doub_lstdelall(&duped, del_f);
			return (NULL);
		}
		new = doub_lstnew(value);
		if (new == NULL)
		{
			doub_lstdelall(&duped, del_f);
			return (NULL);
		}
		doub_lstappend(&duped, new);
		src = src->next;
	}
	return (duped);
}
