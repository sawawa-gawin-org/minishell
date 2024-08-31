/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_envlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:03:56 by saraki            #+#    #+#             */
/*   Updated: 2024/08/31 18:45:10 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"
#include "dbllst.h"
#include "libft.h"

static void	free_until_index(char **result, size_t index);

/**
 * @brief Create an array of environment variables from a linked list.
 *
 * This function takes a linked list of environment variables and converts
 * it into an array of strings. Each string in the array represents
 * an environment variable in the format "name=value".
 * The resulting array is null-terminated.
 *
 * @param env_lst The linked list of environment variables.
 * @param is_val_is_nullable Flag indicating whether the value of
 * an environment variable can be nullable.
 * @return The array of environment variables.
 */
char	**create_env_arr_from_lst(t_blst *env_lst, int is_val_is_nullable)
{
	char	**env_arr;
	char	*key;
	char	*val;
	size_t	i;

	env_arr = (char **) ft_calloc(doub_lstcnt(env_lst) + 1, sizeof(char *));
	i = 0;
	while (env_lst->u_data.env_data != NULL)
	{
		key = env_lst->u_data.env_data->key;
		val = env_lst->u_data.env_data->val;
		if (ft_strcmp(key, "?") != 0 && (val != NULL || is_val_is_nullable))
		{
			env_arr[i] = ft_strjoin_with_sep(key, val, '=');
			if (env_arr[i] == NULL)
			{
				free_until_index(env_arr, i);
				return (NULL);
			}
			i ++;
		}
		env_lst = env_lst->next;
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
