/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_setenv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 08:19:27 by saraki            #+#    #+#             */
/*   Updated: 2024/07/21 19:43:21 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "env.h"

static int	add_env_to_envlst(char *cmd, t_blst **envlst);
static int	overwrite_env(char *key, char *val, t_blst **envlst);

// KEYに予約語が含まれる場合はエラーにする
int	export_env(char **cmd, t_blst **envlst, int mode)
{
	int		i;
	int		err;

	i = 1;
	if (mode == IS_CHILD_PROCESS)
		return (OK);
	if (ft_strcmp(cmd[1], "--") == 0)
		i++;
	while (cmd[i] != NULL)
	{
		err = add_env_to_envlst(cmd[i], envlst);
		if (err == -1)
		{
			export_identifier_err(cmd[i]);
			i++;
			continue ;
		}
		else if (err == ERR_ALLOCATE_MEMORY)
			return (ERR_ALLOCATE_MEMORY);
		i++;
	}
	return (OK);
}

static int	add_env_to_envlst(char *cmd, t_blst **envlst)
{
	char	**key_val;
	int		pos;

	pos = valid_format_key(cmd);
	if (pos == -1)
		return (-1);
	key_val = get_key_val(cmd, pos);
	if (key_val == NULL)
		return (ERR_ALLOCATE_MEMORY);
	if (overwrite_env(key_val[0], key_val[1], envlst) == 1)
		if (add_shell_env(key_val[0], key_val[1], (void **)envlst) == ERR)
			return (ERR_ALLOCATE_MEMORY);
	free(key_val[0]);
	free(key_val[1]);
	free(key_val);
	return (0);
}

static int	overwrite_env(char *key, char *val, t_blst **envlst)
{
	t_blst	*head;

	head = *envlst;
	while ((*envlst)->u_data.env_data != NULL)
	{
		if (ft_strcmp((*envlst)->u_data.env_data->key, key) == 0)
		{
			free((*envlst)->u_data.env_data->val);
			(*envlst)->u_data.env_data->val = ft_strdup(val);
			if ((*envlst)->u_data.env_data->val == NULL)
			{
				*envlst = head;
				return (-1);
			}
			*envlst = head;
			return (0);
		}
		*envlst = (*envlst)->next;
	}
	*envlst = head;
	return (1);
}
