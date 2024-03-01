/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:41:01 by saraki            #+#    #+#             */
/*   Updated: 2023/09/29 16:04:03 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	if (write(fd, s, len) == -1)
		return ;
	return ;
}

// int main()
// {
// 	ft_putstr_fd("abcdefg\n", STDOUT_FILENO);
// 	ft_putstr_fd("abcdefg\n", STDERR_FILENO);
// }
