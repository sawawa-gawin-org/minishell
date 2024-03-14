/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2way.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:27:21 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/14 18:16:06 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static t_lst2way	*lstnew(void);
static t_lst2way	*lstlast(t_lst2way *lst);

t_tok	*allocate_tok(char *str, int type)
{
	t_tok	*new;

	new = (t_tok *)malloc(sizeof(t_tok));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (new->str == NULL)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	return (new);
}

t_lst2way	*lstadd_2way(t_lst2way *lst, void *content)
{
	t_lst2way	*last;
	t_lst2way	*data;

	last = NULL;
	data = NULL;
	data = lstnew();
	if (!data)
		return (NULL);
	data->content = content;
	data->next = NULL;
	data->prev = NULL;
	if (lst != NULL)
	{
		last = lstlast(lst);
		data->prev = last;
		last->next = data;
		return (lst);
	}
	return (data);
}

static t_lst2way	*lstnew(void)
{
	t_lst2way	*new;

	new = (t_lst2way *)malloc(sizeof(t_lst2way));
	if (!new)
		return (NULL);
	return (new);
}

static t_lst2way	*lstlast(t_lst2way *lst)
{
	t_lst2way	*now;
	t_lst2way	*next;

	if (lst == NULL)
		return (lst);
	now = lst;
	next = lst->next;
	while (next != NULL)
	{
		now = next;
		next = next->next;
	}
	return (now);
}
