/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:20:08 by saraki            #+#    #+#             */
/*   Updated: 2024/06/21 05:43:19 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"
#include "dbllst.h"
#include "libft.h"

static int cmp_key(void *data, void *query_pt);

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
	if (old_node != NULL)
	{
		free(old_node->e_data->val);
		old_node->e_data->val = new_status;
		return (OK);
	}
	err = add_shell_env(key, new_status, env_lst);
	free(new_status);
	if (err == ERR)
		return (ERR);
	return (OK);
}

static int cmp_key(void *data, void *query_pt)
{
	t_env_data	*env_data;

	env_data = (t_env_data *)data;
	if (ft_strcmp(env_data->key, (char *)query_pt) == 0)
		return (1);
	return (0);
}

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
