/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 02:43:28 by syamasaw          #+#    #+#             */
/*   Updated: 2024-07-15 02:43:28 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"
#include "env.h"

static int	export_all(t_blst *envlst);
static int	export_env(char **cmd, t_blst **envlst);
static int	overwrite_env(char *key, char *val, t_blst **envlst);
static int	add_env_to_envlst(char *cmd, t_blst **envlst);

int	builtin_export(char **cmd, t_blst **envlst)
{
	int		status;

	status = valid_option(cmd);
	if (status > 0)
		return (status);
	if (!cmd[1] || (ft_strcmp(cmd[1], "--") == 0 && !cmd[2]))
		return (export_all(*envlst));
	return (export_env(cmd, envlst));
}

static int	export_all(t_blst *envlst)
{
	char	**env;
	int		i;

	env = convert_envlst_to_arr(envlst);
	if (env == NULL)
		return (ERR_ALLOCATE_MEMORY);
	i = 0;
	while (env[i] != NULL)
		i++;
	qsort_env(env, 0, i - 1);
	i = 0;
	while (env[i] != NULL)
	{
		if (print_export(env[i]) == GENERAL_ERR)
		{
			free_environment_array(env);
			return (ERR_ALLOCATE_MEMORY);
		}
		i++;
	}
	free_environment_array(env);
	return (OK);
}

// KEYに予約語が含まれる場合はエラーにする
static int	export_env(char **cmd, t_blst **envlst)
{
	int		i;
	int		status;
	int		err;

	i = 1;
	status = 0;
	if (ft_strcmp(cmd[1], "--") == 0)
		i++;
	while (cmd[i] != NULL)
	{
		err = add_env_to_envlst(cmd[i], envlst);
		if (err == -1)
		{
			status = 1;
			export_err(cmd[i], 1);
			i++;
			continue ;
		}
		else if (err == ERR_ALLOCATE_MEMORY)
			return (ERR_ALLOCATE_MEMORY);
		i++;
	}
	return (status);
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
