/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:46:17 by saraki            #+#    #+#             */
/*   Updated: 2023/09/29 16:04:15 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	if (write(fd, s, len) == -1)
		return ;
	ft_putchar_fd('\n', fd);
	return ;
}

// int main()
// {
// 	ft_putendl_fd("abcdefg", STDOUT_FILENO);
// 	ft_putendl_fd("abcdefg", STDERR_FILENO);
// }
