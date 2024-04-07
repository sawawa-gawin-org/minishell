/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:56:18 by saraki            #+#    #+#             */
/*   Updated: 2024/03/30 18:21:40 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

// void	end(void)__attribute__((destructor));

// void	end(void)
// {
// 	system("leaks minishell.out");
// }

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	return (minishell(envp));
}
