/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:10:09 by saraki            #+#    #+#             */
/*   Updated: 2024/08/17 13:49:52 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "dbllst.h"
#include "env.h"
#include "libft.h"

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
 * Updates the PWD and OLDPWD environment variables with the given paths.
 *
 * @param old_pwd The old working directory path.
 * @param new_pwd The new working directory path.
 * @param envlst  A pointer to the linked list of environment variables.
 * @return        Returns OK on success, ERR on failure.
 * @note          It doesn't matter if the both parameters are allocated or not.
 */
int	update_pwd_and_oldpwd_env(char *old_pwd, char *new_pwd, t_blst **envlst)
{
	int		status;

	if (old_pwd == NULL || new_pwd == NULL)
		return (GENERAL_ERR);
	status = OK;
	status = update_or_create_env("OLDPWD", old_pwd, envlst);
	if (status == OK)
		status = update_or_create_env("PWD", new_pwd, envlst);
	return (status);
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
