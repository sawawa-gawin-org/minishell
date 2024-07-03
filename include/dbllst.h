/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbllst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:57:02 by saraki            #+#    #+#             */
/*   Updated: 2024/06/19 13:19:18 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DBLLST_H
# define DBLLST_H

# include <stdlib.h>

// create a new list with `data`
void			*doub_lstnew(void *data);

// push a `new_node` to the front of the `head`
void			doub_lstprepend(void **head, void *new_node);

// push a `new_node` to the back of the `head`
void			doub_lstappend(void **head, void *new_node);

// purge the specified `target` from the list, and return the `target`
// (when given a `target` with NULL, do nothing and return NULL)
void			*doub_lstpurge(void **target);

// clear the all nodes of `lst`  with `del` function
//  `lst` must be the first element of the list
void			doub_lstdelall(void **lst, void *del_f);

// delete(free) the specified item from the `lst` using `del` function
// (Not reconnecting the `lst` after deletion)
void			doub_lstdelone(void *lst, void *del_f);

// duplicate the void structure include all connected nodes
// `dup_f`: function pointer of duplication function
void			*doub_lstdup(void *src, void *dup_f, void *del_f);

// search and return the specified `node` pointer from the `lst`
// `int (cmp_f)(void *, void *)`: return 1 if match
void			*doub_lstsearch(void *lst, void *query_pt, void *cmp_f);

// return the number of nodes in the `lst`
size_t			doub_lstcnt(void *lst);

#endif