/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:56:18 by saraki            #+#    #+#             */
/*   Updated: 2024/03/17 14:57:37 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// void	end(void)__attribute__((destructor));

// void	end(void)
// {
// 	system("leaks minishell.out");
// }

int	main(int argc, char *argv[], char *envp[])
{
	minishell(argc, argv, envp);
	return (0);
}
