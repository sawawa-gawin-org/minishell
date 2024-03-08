/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 05:22:42 by saraki            #+#    #+#             */
/*   Updated: 2024/03/08 09:32:14 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

/* 
- make_*_child関数の中でファイルの展開を行う
- wate_pidはこの関数内で行う
- close_fdは未定
*/

int	spawn_children(char **units, int size, t_pipex *pipex_arr, char **envp)
{
	int		i;
	int		err;

	i = 0;
	err = 0;
	while (i < size)
	{
		if (i == 0)
			err = make_oldest_child(units[i], &pipex_arr[i], envp);
		else if (i == size - 1)
			err = make_youngest_child(units[i], &pipex_arr[i], envp);
		else
			err = make_middle_child(units[i], &pipex_arr[i], envp);
		if (err != 0)
			return (err);
		i ++;
	}
	return (err);
}
