/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 05:22:42 by saraki            #+#    #+#             */
/*   Updated: 2024/03/05 08:51:31 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_int.h"

static	int	count_units(char **units);

int	spawn_children(char **units, int size, t_pipex *pipex_arr, char **envp)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < size)
	{
		if (i == 0)
			ret = make_oldest_child(units[i], envp, &pipex_arr[i]);
		else if (i == size - 1)
			ret = make_youngest_child(units[i], envp, &pipex_arr[i]);
		else
			ret = make_middle_child(units[i], envp, &pipex_arr[i]);
		if (ret != 0)
			return (ret);
		i ++;
	}
	return ret;
}
