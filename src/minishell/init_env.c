/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:48:33 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/24 17:52:58 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "dbllst.h"

static int			strlen_eq(char *str);
static t_blst		*new_env_node(char *str, int flag);
static t_env_data	*new_env_data(char *str, int flag);

void	*init_env(void)
{
	t_blst		*ret;
	t_blst		*new_node;
	extern char	**environ;

	ret = doub_lstnew(NULL);
	while (ret != NULL && *environ != NULL)
	{
		new_node = new_env_node(*environ, 1);
		if (new_node == NULL)
		{
			doub_lstdelall((void **)&ret, free_env_data);
			return (NULL);
		}
		doub_lstappend((void **)&ret, new_node);
		environ ++;
	}
	return ((void *)ret);
}

static t_blst	*new_env_node(char *str, int flag)
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

static t_env_data	*new_env_data(char *str, int flag)
{
	t_env_data	*ret;
	int			len;

	ret = (t_env_data *)malloc(sizeof(t_env_data));
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

static int	strlen_eq(char *str)
{
	int	i;

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
