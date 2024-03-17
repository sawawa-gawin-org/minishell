/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:19:46 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 02:38:21 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

typedef void *(*t_dup_f)(void *);
typedef void (*t_del_f)(void*);

t_dbl_list	*doub_lstdup(t_dbl_list *src, t_dup_f dup_f, t_del_f del_f)
{
	t_dbl_list	*duped;
	t_dbl_list	*new;
	void		*value;

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
