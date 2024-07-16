/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_qsort_env.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-16 03:32:54 by syamasaw          #+#    #+#             */
/*   Updated: 2024-07-16 03:32:54 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static void	swap(char **a, char **b);
static int	partition(char **env, int low, int high);

int	print_export(char *env)
{
	char	**key_val;

	key_val = get_key_val(env);
	if (key_val == NULL)
		return (GENERAL_ERR);
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

static void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int	partition(char **env, int low, int high)
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
