/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:10:09 by saraki            #+#    #+#             */
/*   Updated: 2024/08/07 02:11:14 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "env.h"
#include "libft.h"

static int	update_or_create_env(char *key, char *value, t_blst **envlst);

char	*create_abspath(char *pwdpath, char *relpath)
{
	char	*joined_path;
	size_t	len;

	len = ft_strlen(pwdpath) + 1 + ft_strlen(relpath) + 1;
	joined_path = (char *)ft_calloc(sizeof(char), len);
	if (joined_path == NULL)
		return (NULL);
	ft_strlcat(joined_path, pwdpath, len);
	ft_strlcat(joined_path, "/", len);
	ft_strlcat(joined_path, relpath, len);
	return (joined_path);
}

char	*allocate_cwd_path(t_blst *envlst)
{
	t_blst	*target_node;
	char	*key;
	char	*cwd_path;

	key = "PWD";
	target_node = (t_blst *)doub_lstsearch(envlst, key, cmp_key);
	if (target_node->u_data.env_data == NULL)
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
	t_blst	*old_pwd_node;
	t_blst	*pwd_node;
	int		status;

	if (old_pwd == NULL || new_pwd == NULL)
		return (GENERAL_ERR);
	status = OK;
	old_pwd_node = (t_blst *)doub_lstsearch(*envlst, "OLDPWD", cmp_key);
	pwd_node = (t_blst *)doub_lstsearch(*envlst, "PWD", cmp_key);
	status = update_or_create_env("OLDPWD", old_pwd, envlst);
	if (status == OK)
		status = update_or_create_env("PWD", new_pwd, envlst);
	return (status);
}

static int	update_or_create_env(char *key, char *value, t_blst **envlst)
{
	t_blst	*target_node;
	int		status;
	char	*new_value;

	new_value = ft_strdup(value);
	if (new_value == NULL)
		return (ERR);
	target_node = (t_blst *)doub_lstsearch(*envlst, key, cmp_key);
	if (target_node->u_data.env_data == NULL)
	{
		status = add_shell_env(key, new_value, (void **)envlst);
		if (status == ERR)
		{
			free(new_value);
			return (ERR);
		}
	}
	else
	{
		free(target_node->u_data.env_data->val);
		target_node->u_data.env_data->val = new_value;
	}
	return (OK);
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
	if (target_node->u_data.env_data == NULL)
		return (cd_home_not_set_err());
	*path = target_node->u_data.env_data->val;
	return (OK);
}
