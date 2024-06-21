/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbllst_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:57:02 by saraki            #+#    #+#             */
/*   Updated: 2024/06/19 13:19:10 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DBLLST_INT_H
# define DBLLST_INT_H

# include <stdlib.h>

typedef struct s_node
{
	struct s_node	*prev;
	void			*data;
	struct s_node	*next;
}				t_blst;

typedef void	*(*t_dup_f)(void *);
typedef void	(*t_del_f)(void *);
typedef int		(*t_cmp_f)(void *, void *);

// create a new list with `data`
t_blst			*doub_lstnew(void *data);

// push a `new_node` to the front of the `head`
void			doub_lstprepend(t_blst **head, t_blst *new_node);

// push a `new_node` to the back of the `head`
void			doub_lstappend(t_blst **head, t_blst *new_node);

// purge the specified `target` from the list, and return the `target`
// (when given a `target` with NULL, do nothing and return NULL)
t_blst			*doub_lstpurge(t_blst **target);

// clear the all nodes of `lst`  with `del` function
//  `lst` must be the first element of the list
void			doub_lstdelall(t_blst **lst, t_del_f del_f);

// delete(free) the specified item from the `lst` using `del` function
// (Not reconnecting the `lst` after deletion)
void			doub_lstdelone(t_blst *lst, t_del_f del_f);

// duplicate the t_blst structure include all connected nodes
// `dup_f`: function pointer of duplication function
t_blst			*doub_lstdup(t_blst *src, t_dup_f dup_f, t_del_f del_f);

// search and return the specified `node` pointer from the `lst`
// `int (cmp_f)(void *, void *)`: return 1 if match
t_blst			*doub_lstsearch(t_blst *lst, void *query_pt, t_cmp_f cmp_f);

// return the number of nodes in the `lst`
size_t			doub_lstcnt(t_blst *lst);

#endif