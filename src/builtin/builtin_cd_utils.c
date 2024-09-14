/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:10:09 by saraki            #+#    #+#             */
/*   Updated: 2024/09/14 14:59:14 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "dbllst.h"
#include "env.h"
#include "libft.h"
#include "path.h"

static int	cwd_check(char *path, t_cd_path_routing *routing);

char	*allocate_cwd_path(t_blst *envlst)
{
	t_blst	*target_node;
	char	*key;
	char	*cwd_path;

	key = "PWD";
	target_node = (t_blst *)doub_lstsearch(envlst, key, cmp_key);
	if (target_node->u_data.env_data == NULL
		|| target_node->u_data.env_data->val == NULL)
	{
		cwd_path = getcwd(NULL, 0);
		if (cwd_path == NULL)
			return (NULL);
		return (cwd_path);
	}
	return (ft_strdup(target_node->u_data.env_data->val));
}

/**
 * @brief Get the home path.
 *
 * This function retrieves the home path from the environment list
 * and stores it in the `path` variable.
 *
 * @param path The pointer to the variable where the home path will be stored.
 * @param envlst The environment list.
 *
 * @return The status code indicating the success or failure of the operation.
 * @note This function does not allocate memory for the `path` variable.
 */
int	get_home_path(char **path, t_blst *envlst)
{
	t_blst	*target_node;

	target_node = (t_blst *)doub_lstsearch(envlst, "HOME", cmp_key);
	if (target_node->u_data.env_data == NULL
		|| target_node->u_data.env_data->val == NULL)
		return (cd_home_not_set_err());
	if (ft_strcmp(target_node->u_data.env_data->val, "") == 0)
		*path = getenv("HOME");
	else
		*path = target_node->u_data.env_data->val;
	if (*path == NULL)
		return (cd_home_not_set_err());
	return (OK);
}

int	get_oldpwd_path(char **path, t_blst *envlst)
{
	t_blst	*target_node;

	target_node = (t_blst *)doub_lstsearch(envlst, "OLDPWD", cmp_key);
	if (target_node->u_data.env_data == NULL
		|| target_node->u_data.env_data->val == NULL)
		return (cd_oldpwd_not_set_err());
	if (ft_strcmp(target_node->u_data.env_data->val, "") == 0)
		*path = NULL;
	else
		*path = target_node->u_data.env_data->val;
	if (*path == NULL)
		return (cd_oldpwd_not_set_err());
	return (OK);
}

int	cd_check_err(char *path, t_cd_path_routing *routing)
{
	int	err;

	if (chdir(routing->dist) == 0)
		return (OK);
	err = cwd_check(path, routing);
	if (err)
		return (err);
	if (!is_directory(routing->dist))
		cd_not_a_directory_err(path);
	else if (access(routing->dist, F_OK) == 0
		&& access(routing->dist, X_OK) != 0)
		cd_permission_err(path);
	else
		cd_no_such_file_err(path);
	if (routing->src != NULL)
		free(routing->src);
	if (routing->dist != NULL)
		free(routing->dist);
	return (GENERAL_ERR);
}

static int	cwd_check(char *path, t_cd_path_routing *routing)
{
	char	*tmp;
	char	cwd[PATHNAME_SIZE];

	if (getcwd(cwd, PATHNAME_SIZE) == NULL)
	{
		cd_cwd_error();
		tmp = ft_strjoin_with_sep(routing->src, path, '/');
		if (tmp == NULL)
		{
			malloc_error();
			return (ERR_ALLOCATE_MEMORY);
		}
		free(routing->dist);
		routing->dist = tmp;
		return (ERR);
	}
	return (OK);
}
