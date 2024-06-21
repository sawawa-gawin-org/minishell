/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_envlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:03:56 by saraki            #+#    #+#             */
/*   Updated: 2024/06/21 14:07:32 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"
#include "dbllst.h"
#include "libft.h"

static void	free_until_index(char **result, size_t index);

char	**convert_envlst_to_arr(t_blst *env_lst)
{
	char	**env_arr;
	char	*keyvalue;
	size_t	i;

	env_arr = (char **) ft_calloc(doub_lstcnt(env_lst) + 1, sizeof(char *));
	i = 0;
	while (env_lst->e_data != NULL)
	{
		if (!ft_strcmp(env_lst->e_data->key, "?"))
		{
			env_lst = env_lst->next;
			continue ;
		}
		keyvalue = join_keyval(env_lst->e_data->key, env_lst->e_data->val);
		if (keyvalue == NULL)
		{
			free_until_index(env_arr, i);
			return (NULL);
		}
		env_arr[i] = keyvalue;
		env_lst = env_lst->next;
		i ++;
	}
	return (env_arr);
}

void	free_environment_array(char **env)
{
	size_t	array_size;

	array_size = 0;
	while (env[array_size] != NULL)
		array_size ++;
	free_until_index(env, array_size + 1);
	return ;
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
