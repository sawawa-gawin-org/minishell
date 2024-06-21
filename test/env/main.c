/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 06:35:09 by saraki            #+#    #+#             */
/*   Updated: 2024/06/21 06:57:55 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "dbllst.h"
#include "libft.h"

void	end(void)__attribute__((destructor));

void	end(void)
{
	system("leaks env.out");
}

int main(int argc, char **argv, char **envp)
{
	void	*env_lst;
	char	**env_arr;

	(void)argc;
	(void)argv;
	env_lst = init_env(envp);
	env_arr = convert_envlst_to_arr(env_lst);
	free_environment_array(env_arr);
	doub_lstdelall(&env_lst, free_env_data);
	return (0);
}
