/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doub_lstsearch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:34:48 by saraki            #+#    #+#             */
/*   Updated: 2024/03/18 02:52:11 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"

typedef int (t_cmp_f)(void *, void *);

t_dbl_list	*doub_lstsearch(t_dbl_list *lst, void *query_pt, t_cmp_f cmp_f)
{
	t_dbl_list	*ret_node;
	int		i;

	if (lst == NULL)
		return (NULL);
	i = 0;
	ret_node = lst;
	while (ret_node->data != NULL)
	{
		if (cmp_f(ret_node->data, query_pt))
			return (ret_node);
		ret_node = ret_node->next;
		i ++;
	}
	return (ret_node);
}
