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
