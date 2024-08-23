/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:55:37 by root              #+#    #+#             */
/*   Updated: 2024/06/26 14:19:28 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	syntax_unexpected_error(char *token)
{
	char	*prefix;
	char	*suffix;
	char	*msg;

	prefix = MSG_PREFIX;
	msg = "syntax error near unexpected token `";
	suffix = "'\n";
	if (write(STDERR_FILENO, prefix, ft_strlen(prefix)) == -1)
		perror("write");
	if (write(STDERR_FILENO, msg, ft_strlen(msg)) == -1)
		perror("write");
	if (write(STDERR_FILENO, token, ft_strlen(token)) == -1)
		perror("write");
	if (write(STDERR_FILENO, suffix, ft_strlen(suffix)) == -1)
		perror("write");
	return (ERR);
}

int	syntax_unclose_quote_error(void)
{
	char	*prefix;
	char	*msg;

	prefix = MSG_PREFIX;
	msg = "not interpret unclosed quotes\n";
	if (write(STDERR_FILENO, prefix, ft_strlen(prefix)) == -1)
		perror("write");
	if (write(STDERR_FILENO, msg, ft_strlen(msg)) == -1)
		perror("write");
	return (ERR);
}

int	branching_syntax_err_by_flag(int flag)
{
	if (flag & TUBE_FLAG)
		return (syntax_unexpected_error("|"));
	else
		return (syntax_unexpected_error("newline"));
	return (ERR);
}
