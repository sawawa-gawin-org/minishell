/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 05:15:47 by saraki            #+#    #+#             */
/*   Updated: 2024/03/05 05:16:53 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_int.h"

char	*join_args_with_space(int argc, char **argv)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 1;
	ret = "";
	if (argv == NULL || *argv == NULL)
		return (NULL);
	while (i < argc)
	{
		ret = ft_strjoin(ret, argv[i]);
		if (ret == NULL)
			return (NULL);
		tmp = ret;
		if (argc - 1 != i)
		{	
			ret = ft_strjoin(tmp, " ");
			free(tmp);
			if (ret == NULL)
				return (NULL);
		}
		i++;
	}
	return (ret);
}
