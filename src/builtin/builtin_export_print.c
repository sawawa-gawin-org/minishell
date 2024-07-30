/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 08:43:55 by saraki            #+#    #+#             */
/*   Updated: 2024/07/21 18:48:20 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "env.h"

static int	print_each_env(char *env);

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
		if (print_each_env(env[i]) == GENERAL_ERR)
		{
			free_environment_array(env);
			return (ERR_ALLOCATE_MEMORY);
		}
		i++;
	}
	free_environment_array(env);
	return (OK);
}

static int	print_each_env(char *env)
{
	char	**key_val;
	int		pos;

	if (ft_strncmp(env, "_=", 2) == 0)
		return (OK);
	pos = valid_format_key(env);
	if (pos == -1)
		return (GENERAL_ERR);
	key_val = get_key_val(env, pos);
	if (key_val == NULL)
		return (ERR_ALLOCATE_MEMORY);
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(key_val[0], 1);
	if (ft_strcmp(key_val[1], "") != 0)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(key_val[1], 1);
		ft_putendl_fd("\"", 1);
	}
	else
		ft_putchar_fd('\n', 1);
	free(key_val[0]);
	free(key_val[1]);
	free(key_val);
	return (OK);
}
