/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:19:46 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 03:16:27 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"

t_bi_lst	*doub_lstdup(t_bi_lst *src, t_dup_f dup_f, t_del_f del_f)
{
	t_bi_lst	*duped;
	t_bi_lst	*new;
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
