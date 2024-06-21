/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_envlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:03:56 by saraki            #+#    #+#             */
/*   Updated: 2024/06/19 13:27:18 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"
#include "dbllst.h"
#include "libft.h"

static void	free_until_index(char **result, size_t index);

char	**convert_envlst_to_arr(void *env_lst)
{
	t_blst	*node;
	size_t	list_size;
	char	**env_arr;
	char	*keyvalue;
	size_t	i;

	list_size = doub_lstcnt(env_lst);
	env_arr = (char **) ft_calloc(list_size + 1, sizeof(char *));
	node = (t_blst *)env_lst;
	i = 0;
	while (node->e_data != NULL)
	{
		keyvalue = join_keyval(node->e_data->key, node->e_data->val);
		if (keyvalue == NULL)
		{
			free_until_index(env_arr, i);
			return (NULL);
		}
		env_arr[i] = keyvalue;
		node = node->next;
		i ++;
	}
	return (env_arr);
}

static void	free_until_index(char **result, size_t index)
{
	unsigned int	i;

	i = 0;
	while (i < index)
	{
		free(result[i]);
		i ++;
	}
	free(result);
	return ;
}
