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
static int	valid_format(char *cmd);
static char	**get_key_val(char *cmd);
static int	export_env(char **cmd, t_blst **envlst);

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
	i = 0;
	while (env[i] != NULL)
		i++;
	qsort_env(env, 0, i - 1);
	i = 0;
	while (env[i] != NULL)
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	free_environment_array(env);
	return (OK);
}

static int	valid_format(char *cmd)
{
	int	pos;

	pos = 0;
	if (cmd[0] == '\0')
		return (-1);
	if (('0' <= cmd[0] && cmd[0] <= '9') || cmd[0] == '=')
		return (-1);
	while (cmd[pos] != '\0')
	{
		if (ft_strchr("!@#-* ", cmd[pos]))
			return (-1);
		if (cmd[pos] == '=')
			break ;
		pos++;
	}
	return (pos);
}

static char	**get_key_val(char *cmd)
{
	char	**key_val;
	int		pos;

	pos = valid_format(cmd);
	if (pos == -1)
		return (NULL);
	key_val = (char **)ft_calloc(2, sizeof(char *));
	if (key_val == NULL)
		return (NULL);
	key_val[0] = ft_substr(cmd, 0, pos);
	if (key_val[0] == NULL)
		return (NULL);
	if (cmd[pos] == '\0')
		key_val[1] = ft_strdup("");
	else
		key_val[1] = ft_strdup(cmd + pos + 1);
	if (key_val[1] == NULL)
	{
		free(key_val[0]);
		return (NULL);
	}
	return (key_val);
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
		add_shell_env(key_val[0], key_val[1], (void **)envlst);
		free(key_val[0]);
		free(key_val[1]);
		free(key_val);
		i++;
	}
	return (OK);
}
