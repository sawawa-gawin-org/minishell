/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 06:35:09 by saraki            #+#    #+#             */
/*   Updated: 2024/08/31 18:39:25 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "dbllst.h"
#include "libft.h"

#include <stdio.h>

void	print_env_arr(char **env);

int	main(int argc, char **argv, char **envp)
{
	void	*env_lst;
	char	**env_arr;

	(void)argc;
	(void)argv;
	(void)envp;
	env_lst = create_envlist(envp);
	env_arr = create_env_arr_from_lst(env_lst, 0);
	print_env_arr(env_arr);
	printf("-------------------\n");
	print_env(env_lst);
	free_environment_array(env_arr);
	doub_lstdelall(&env_lst, free_env_data);
	return (0);
}

void	print_env_arr(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
