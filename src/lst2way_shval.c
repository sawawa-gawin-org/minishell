/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2way_shval.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:17:38 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/14 20:30:16 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_shval	*lstlast_shval(t_shval *shvals)
{
	if (shvals == NULL)
		return (NULL);
	while (shvals->next != NULL)
		shvals = shvals->next;
	return (shvals);
}

t_shval	*lstnew_shval(void)
{
	t_shval	*new;

	new = (t_shval *)malloc(sizeof(t_shval));
	if (!new)
		return (NULL);
	return (new);
}

t_shval	*lstadd_shval(t_shval *shvals, char *str, int len, int flag)
{
	t_shval	*lst_last_addr;
	t_shval	*data;

	lst_last_addr = NULL;
	data = NULL;
	data = lstnew_shval();
	data->key = ft_substr(str, 0, len);
	data->val = ft_substr(str, len + 1, ft_strlen(str) - (len + 1));
	data->exported = flag;
	data->next = NULL;
	data->prev = NULL;
	if (shvals != NULL)
	{
		lst_last_addr = lstlast_shval(shvals);
		data->prev = lst_last_addr;
		lst_last_addr->next = data;
		return (shvals);
	}
	return (data);
}

void	put_lst_shval(t_shval *shvals)
{
	while (shvals != NULL)
	{
		printf("key: %s val: %s\n", shvals->key, shvals->val);
		shvals = shvals->next;
	}
}

void	del_lst_shval(t_shval *shvals)
{
	while (shvals->next != NULL)
	{
		shvals = shvals->next;
		free(shvals->prev->val);
		free(shvals->prev->key);
		free(shvals->prev);
	}
	free(shvals->val);
	free(shvals->key);
	free(shvals);
}
