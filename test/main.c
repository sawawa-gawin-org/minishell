/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:56:18 by saraki            #+#    #+#             */
/*   Updated: 2024/03/28 17:11:52 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	end(void)__attribute__((destructor));

void	end(void)
{
	system("leaks minishell.out");
}

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	(void) envp;
	char	*str[] = {"echo  hello \"world\", \"asdf\" $NAME \'NAME\'"};
	char	*ret;
	int		type;

	int size = sizeof(str) / sizeof(str[0]);
	for (int i = 0; i < size; i++)
	{
		while (str[i] != NULL)
		{
			ret = allocate_next_token(&str[i], &type);
			printf("%s-%d\n", ret, type);
			free(ret);
		}
	}
	// minishell(argc, argv, envp);
	return (0);
}
