/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:37:15 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/18 05:30:08 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "dbllst.h"

static	t_blst			*new_shval_node(char *str, int flag);
static	t_shval_data	*new_shval_data(char *str, int flag);

int	strlen_eq(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

t_shval	*get_env_all(char **envp, t_shval *shvals)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		shvals = lstadd_shval(shvals, envp[i], strlen_eq(envp[i]), 1);
	}
	return (shvals);
}

void	*new_get_env_all(char **envp)
{
	t_blst			*ret;
	t_blst			*new_node;
	t_shval_data	*shval;

	ret = doub_lstnew(NULL);
	if (ret == NULL)
		return (NULL);
	while (*envp != NULL)
	{
		new_node = new_shval_node(*envp, 1);
		if (new_node == NULL)
		{
			doub_lstdelall(&ret, free_shval_data);
			return (NULL);
		}
		doub_lstappend(&ret, new_node);
		envp ++;
	}
	return ((void *)ret);
}

static	t_blst	*new_shval_node(char *str, int flag)
{
	t_blst			*node;
	t_shval_data	*data;
	
	data = new_shval_data(str, flag);
	if (data == NULL)
		return (NULL);
	node = doub_lstnew((void *)data);
	if (node == NULL)
	{
		free_shval_data(data);
		return (NULL);
	}
	return (node);
}

static	t_shval_data	*new_shval_data(char *str, int flag)
{
	t_shval_data	*ret;
	int				len;

	ret = (t_shval_data *)malloc(sizeof(t_shval_data));
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

void	free_shval_data(void *data)
{
	t_shval_data	*shval;

	shval = (t_shval_data *)data;
	if (shval == NULL)
		return ;
	if (shval->key != NULL)
		free(shval->key);
	if (shval->val != NULL)
		free(shval->val);
	free(shval);
}
