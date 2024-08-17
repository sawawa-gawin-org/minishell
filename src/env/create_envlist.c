/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 07:23:57 by saraki            #+#    #+#             */
/*   Updated: 2024/08/17 06:06:33 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"
#include "dbllst.h"
#include "libft.h"

static size_t		strlen_eq(char *str);
static	t_blst		*new_env_node(char *str, int flag);

/**
 * Create env_list from the environment variables array.
 *
 * @param env An array of strings representing the environment variables.
 * @return A pointer to the initialized environment list.
 */
t_blst	*create_envlist(char **env)
{
	t_blst		*ret;
	t_blst		*new_node;
	int			i;

	i = 0;
	ret = doub_lstnew(NULL);
	if (add_exit_status_as_env((void **)&ret, 0))
	{
		doub_lstdelall((void **)&ret, free_env_data);
		return (NULL);
	}
	while (ret != NULL && env[i] != NULL)
	{
		new_node = new_env_node(env[i], NOT_EXPORTED);
		if (new_node == NULL)
		{
			doub_lstdelall((void **)&ret, free_env_data);
			return (NULL);
		}
		doub_lstappend((void **)&ret, new_node);
		i ++;
	}
	return ((void *)ret);
}

static	t_blst	*new_env_node(char *str, int flag)
{
	t_blst		*node;
	t_env_data	*data;

	data = new_env_data(str, flag);
	if (data == NULL)
		return (NULL);
	node = doub_lstnew((void *)data);
	if (node == NULL)
	{
		free_env_data(data);
		return (NULL);
	}
	return (node);
}

t_env_data	*new_env_data(char *str, int flag)
{
	t_env_data	*ret;
	size_t		len;

	ret = (t_env_data *)ft_calloc(sizeof(t_env_data), 1);
	if (ret == NULL)
		return (NULL);
	len = strlen_eq(str);
	ret->exported = flag;
	ret->key = ft_substr(str, 0, len);
	if (ret->key == NULL)
	{
		free(ret);
		return (NULL);
	}
	ret->val = ft_substr(str, len + 1, ft_strlen(str) - (len + 1));
	if (ret->val == NULL)
	{
		free(ret->key);
		free(ret);
		return (NULL);
	}
	return (ret);
}

static size_t	strlen_eq(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

void	free_env_data(void *data)
{
	t_env_data	*env;

	env = (t_env_data *)data;
	if (env == NULL)
		return ;
	if (env->key != NULL)
		free(env->key);
	if (env->val != NULL)
		free(env->val);
	free(env);
}
