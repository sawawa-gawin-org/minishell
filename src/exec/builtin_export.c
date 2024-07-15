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

int	builtin_export(char **cmd, t_blst **envlst)
{
	if (!cmd[1])
		return (export_all(*envlst));
	if (cmd[1][0] == '-')
	{
		printf("minishell: export: `%s': not a valid identifier\n", cmd[1]);
		return (GENERAL_ERR);
	}
	// return (export_env(cmd[1], envlst));
	return (OK);
}

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	partition(char **env, int low, int high)
{
	char	*pivot;
	int		i;
	int		j;

	pivot = env[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (ft_strcmp(env[j], pivot) < 0)
		{
			i++;
			swap(&env[i], &env[j]);
		}
		j++;
	}
	swap(&env[i + 1], &env[high]);
	return (i + 1);
}

void	qsort_env(char **env, int low, int high)
{
	int	p;

	if (low < high)
	{
		p = partition(env, low, high);
		qsort_env(env, low, p - 1);
		qsort_env(env, p + 1, high);
	}
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
