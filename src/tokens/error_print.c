/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 03:31:04 by saraki            #+#    #+#             */
/*   Updated: 2024/05/15 05:30:27 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

void	error_println(char *str)
{
	char	*prefix;
	char	*suffix;

	prefix = "minishell: ";
	suffix = "\n";
	if (write(STDERR_FILENO, prefix, ft_strlen(prefix)) == -1)
		fatal_println("write");
	if (write(STDERR_FILENO, str, ft_strlen(str)) == -1)
		fatal_println("write");
	if (write(STDERR_FILENO, suffix, ft_strlen(suffix)) == -1)
		fatal_println("write");
	return ;
}

int	syntax_error(char *token)
{
	char	*prefix;
	char	*suffix;
	char	*msg;

	prefix = "minishell: ";
	msg = "syntax error near unexpected token `";
	suffix = "'\n";
	if (write(STDERR_FILENO, prefix, ft_strlen(prefix)) == -1)
		fatal_println("write");
	if (write(STDERR_FILENO, msg, ft_strlen(msg)) == -1)
		fatal_println("write");
	if (write(STDERR_FILENO, token, ft_strlen(token)) == -1)
		fatal_println("write");
	if (write(STDERR_FILENO, suffix, ft_strlen(suffix)) == -1)
		fatal_println("write");
	return (ERR);
}

// print error message and exit
void	fatal_println(char *str)
{
	perror(str);
}
