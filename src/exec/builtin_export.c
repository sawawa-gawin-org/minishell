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

int	builtin_export(char **cmd, t_blst **envlst)
{
	if (!cmd[1])
		return (export_all(*envlst));
	if (cmd[1][0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (GENERAL_ERR);
	}
	return (export_env(cmd, envlst));
}

static int	export_all(t_blst *envlst)
{
	char	**env;
	int		i;

	env = convert_envlst_to_arr(envlst);
	if (env == NULL)
		return (GENERAL_ERR);
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
			return (GENERAL_ERR);
		}
		i++;
	}
	free_environment_array(env);
	return (OK);
}

static int	export_env(char **cmd, t_blst **envlst)
{
	int		i;
	char	**key_val;

	i = 1;
	while (cmd[i] != NULL)
	{
		// KEYに予約語が含まれる場合はエラーにする
		key_val = get_key_val(cmd[i]);
		if (key_val == NULL)
			return (GENERAL_ERR);
		if (overwrite_env(key_val[0], key_val[1], envlst) == 1)
			add_shell_env(key_val[0], key_val[1], (void **)envlst);
		free(key_val[0]);
		free(key_val[1]);
		free(key_val);
		i++;
	}
	return (OK);
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
