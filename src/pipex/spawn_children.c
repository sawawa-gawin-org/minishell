/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 05:22:42 by saraki            #+#    #+#             */
/*   Updated: 2024/03/05 06:06:49 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_int.h"

static	int	count_units(char **units);

void	spawn_children(char **units, int size, t_pipex *pipex, char **envp)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (i == 0)
			make_oldest_child(units[i], envp, pipex);
		else if (i == size - 1)
			make_youngest_child(units[i], envp, pipex);
		else
			make_middle_child(units[i], envp, pipex);
		i ++;
	}
	return ;
}
