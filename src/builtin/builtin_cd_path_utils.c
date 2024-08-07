/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_path_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:44:28 by saraki            #+#    #+#             */
/*   Updated: 2024/08/07 00:34:08 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "env.h"
#include "dbllst.h"
#include "libft.h"

static t_blst	*split_path_elements(char *abspath);
static char		*join_path_nodes(t_blst *path_node);
static size_t	count_string_array(char **arr);
static void		*free_path_arr(char **path_arr, size_t arr_size);

char	*path_resolving(char *abspath)
{
	t_blst	*path_node;
	t_blst	*now_node;
	char	*resolved_path;

	path_node = split_path_elements(abspath);
	if (path_node == NULL)
		return (NULL);
	now_node = path_node;
	while (now_node->u_data.str != NULL)
	{
		if (ft_strcmp(now_node->u_data.str, ".") == 0)
			doub_lstdelone(doub_lstpurge((void **)&now_node), free);
		else if (ft_strcmp(now_node->u_data.str, "..") == 0)
		{
			doub_lstdelone(doub_lstpurge((void **)&(now_node->prev)), free);
			doub_lstdelone(doub_lstpurge((void **)&now_node), free);
		}
		now_node = now_node->next;
	}
	resolved_path = join_path_nodes(path_node);
	doub_lstdelall((void **)&path_node, free);
	return (resolved_path);
}

static t_blst	*split_path_elements(char *abspath)
{
	char			**path_arr;
	t_blst			*node;
	t_blst			*ret;
	size_t			arr_size;
	size_t			i;

	path_arr = ft_split(abspath, '/');
	if (path_arr == NULL)
		return (NULL);
	i = 0;
	arr_size = count_string_array(path_arr);
	ret = doub_lstnew(NULL);
	while (ret != NULL && i < arr_size)
	{
		node = doub_lstnew((void *) path_arr[i]);
		if (node == NULL)
		{
			doub_lstdelall((void **) &ret, NULL);
			return (free_path_arr(path_arr, arr_size));
		}
		doub_lstappend((void **)&ret, node);
		i ++;
	}
	free(path_arr);
	return (ret);
}

static char	*join_path_nodes(t_blst *path_node)
{
	char	*joined_path;
	char	*tmp_path;
	size_t	len;

	joined_path = ft_strdup("");
	if (joined_path == NULL)
		return (NULL);
	while (path_node->u_data.str != NULL)
	{
		len = ft_strlen(joined_path) + ft_strlen(path_node->u_data.str) + 2;
		tmp_path = ft_calloc(sizeof(char), len);
		if (tmp_path == NULL)
		{
			free(joined_path);
			return (NULL);
		}
		ft_strlcat(tmp_path, joined_path, ft_strlen(joined_path) + 1);
		ft_strlcat(tmp_path, "/", ft_strlen(joined_path) + 1 + 1);
		ft_strlcat(tmp_path, path_node->u_data.str, len);
		free(joined_path);
		joined_path = tmp_path;
		path_node = path_node->next;
	}
	return (joined_path);
}

static void	*free_path_arr(char **path_arr, size_t arr_size)
{
	size_t	i;

	i = 0;
	while (i < arr_size)
	{
		if (path_arr[i] != NULL)
			free(path_arr[i]);
		i++;
	}
	free(path_arr);
	return (NULL);
}

static size_t	count_string_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
