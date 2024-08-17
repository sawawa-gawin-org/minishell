/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:15:48 by saraki            #+#    #+#             */
/*   Updated: 2024/08/16 13:27:41 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "env.h"

static int	identify_key_value(
				char *cmd, char *equal, char **key, char **value);
static void	print_each_env(char *env);

//TODO: KEYに予約語が含まれる場合はエラーにする?
int	export_env(char **cmd, t_blst **envlst, int mode)
{
	char	*key;
	char	*equal;
	char	*value;

	if (mode == IS_CHILD_PROCESS)
		return (OK);
	while (*cmd != NULL)
	{
		if (ft_strcmp(*cmd, "") == 0)
			return (export_identifier_err(*cmd));
		equal = ft_strchr(*cmd, '=');
		if (identify_key_value(*cmd, equal, &key, &value))
			return (GENERAL_ERR);
		if (update_or_create_env(key, value, envlst))
			return (ERR_ALLOCATE_MEMORY);
		cmd++;
	}
	return (OK);
}

static int	identify_key_value(
				char *cmd, char *equal, char **key, char **value)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (equal == NULL)
		*value = cmd + len;
	else
		*value = equal + 1;
	*key = cmd;
	if (*key == equal || ft_isdigit((*key)[0]))
		return (export_identifier_err(cmd));
	if (equal != NULL)
		*equal = '\0';
	return (OK);
}


int	export_print(t_blst *envlst, int mode)
{
	char		**env;
	size_t		i;

	if (mode == IS_MAIN_PROCESS)
		return (OK);
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
		print_each_env(env[i]);
		i++;
	}
	free_environment_array(env);
	return (OK);
}

static void	print_each_env(char *env)
{
	char	*key;
	char	*equal;
	char	*value;

	if (ft_strncmp(env, "_=", 2) == 0)
		return ;
	equal = ft_strchr(env, '=');
	value = equal + 1;
	key = env;
	*equal = '\0';
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(key, 1);
	if (value[0] != '\0')
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(value, 1);
		ft_putendl_fd("\"", 1);
	}
	else
		ft_putendl_fd("", 1);
	return ;
}
