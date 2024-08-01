/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:20:08 by saraki            #+#    #+#             */
/*   Updated: 2024/08/01 15:00:34 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"
#include "dbllst.h"
#include "libft.h"

/**
 * Adds the exit status as an environment variable.
 *
 * This function takes a pointer to a list of environment variables
 * and an exit status as input. It adds the exit status as a new environment
 * variable to the list.
 *
 * @param env_lst A pointer to a list of environment variables.
 * @param status The exit status to be added as an environment variable.
 * @return Returns 0 on success, -1 on failure.
 */
int	add_exit_status_as_env(void **env_lst, int status)
{
	t_blst		*old_node;
	char		*key;
	int			err;
	char		*new_status;

	new_status = ft_itoa(status);
	if (new_status == NULL)
		return (ERR);
	key = "?";
	old_node = (t_blst *)doub_lstsearch(*env_lst, key, cmp_key);
	if (old_node->u_data.env_data != NULL)
	{
		free(old_node->u_data.env_data->val);
		old_node->u_data.env_data->val = new_status;
		return (OK);
	}
	err = add_shell_env(key, new_status, env_lst);
	free(new_status);
	if (err == ERR)
		return (ERR);
	return (OK);
}

int	cmp_key(void *data, void *query_pt)
{
	t_env_data	*env_data;

	env_data = (t_env_data *)data;
	if (ft_strcmp(env_data->key, (char *)query_pt) == 0)
		return (1);
	return (0);
}

/**
 * Adds a new environment variable to the shell environment list.
 *
 * @param key The key of the environment variable.
 * @param val The value of the environment variable.
 * @param env_lst A pointer to the shell environment list.
 * @return Returns 0 on success, ERR on failure.
 */
int	add_shell_env(char *key, char *val, void **env_lst)
{
	t_blst		*new_node;
	t_env_data	*new_data;
	char		*key_value;

	key_value = join_keyval(key, val);
	if (key_value == NULL)
		return (ERR);
	new_data = new_env_data(key_value, 0);
	free(key_value);
	if (new_data == NULL)
		return (ERR);
	new_node = doub_lstnew((void *)new_data);
	if (new_node == NULL)
	{
		free_env_data(new_data);
		return (ERR);
	}
	doub_lstappend(env_lst, new_node);
	return (OK);
}

/**
 * Joins a key and a value together.
 *
 * This function takes two strings, `key` and `val`, and concatenates
 * them together, separating them with a delimiter. The resulting
 * string is returned.
 *
 * @param key The key string.
 * @param val The value string.
 * @return The joined string.
 */
char	*join_keyval(char *key, char *val)
{
	char	*ret;
	size_t	key_len;
	size_t	val_len;

	key_len = ft_strlen(key);
	val_len = ft_strlen(val);
	ret = (char *)malloc(sizeof(char) * (key_len + val_len + 2));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, key, key_len + 1);
	ret[key_len] = '=';
	ft_strlcpy(ret + key_len + 1, val, val_len + 1);
	return (ret);
}
