/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:41:53 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/08 09:34:41 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

// void	end(void)__attribute__((destructor));

// void	end(void)
// {
// 	system("leaks pipex.out");
// }

int	main(int argc, char *argv[], char *envp[])
{
	pipex(argc, argv, envp);
	return (0);
}
