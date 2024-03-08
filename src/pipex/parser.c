/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 05:15:47 by saraki            #+#    #+#             */
/*   Updated: 2024/03/08 09:26:03 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static char *join_args_with_space(int argc, char **argv);

char	**parse_argv(int argc, char **argv)
{
	char	**argv_units;
	char	*joined_argv;

	if (argv == NULL || *argv == NULL)
		return (NULL);
	joined_argv = join_args_with_space(argc, argv);
	if (joined_argv == NULL)
		return (NULL);
	argv_units = ft_split(joined_argv, '|');
	if (argv_units == NULL)
	{
		free(joined_argv);
		return (NULL);
	}
	return (argv_units);
}

char	*join_args_with_space(int argc, char **argv)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 1;
	ret = "";
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
