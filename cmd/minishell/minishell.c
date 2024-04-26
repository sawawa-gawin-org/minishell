/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:56:18 by saraki            #+#    #+#             */
/*   Updated: 2024/04/26 18:38:26 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	end(void)__attribute__((destructor));

// void	end(void)
// {
// 	system("leaks minishell");
// }

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	minishell(envp);
	return (0);
}
