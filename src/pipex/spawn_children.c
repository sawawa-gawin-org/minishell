/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 05:22:42 by saraki            #+#    #+#             */
/*   Updated: 2024/03/05 05:36:19 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_int.h"

static	int	count_units(char **units);

void	spawn_children(char **units, t_pipex pipex, char **envp)
{
	int		size;
	int		i;

	size = count_units(units);
	i = 0;
	while (i < size)
	{
		if (i == 0)
			make_oldest_child(units[i], envp, &pipex);
		else if (i == size - 1)
			make_youngest_child(units[i], envp, &pipex);
		else
			make_middle_child(units[i], envp, &pipex);
		i ++;
	}
	return ;
}

static	int	count_units(char **units)
{
	int	count;

	count = 0;
	while (*units = '\0')
	{
		count ++;	
		units ++;
	}
	return (count);
}
