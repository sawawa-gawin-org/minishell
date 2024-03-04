/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:49:25 by saraki            #+#    #+#             */
/*   Updated: 2023/08/19 18:42:48 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	dec_to_str(unsigned int nbr, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	value;

	if (n < 0)
	{
		value = -1 * n;
		ft_putchar_fd('-', fd);
	}
	else
		value = n;
	dec_to_str(value, fd);
}

static void	dec_to_str(unsigned int n, int fd)
{
	int		residual;
	char	print_char;

	if (n < 10)
	{
		print_char = (char)(n + (int) '0');
		ft_putchar_fd(print_char, fd);
		return ;
	}
	residual = n % 10;
	print_char = (char)(residual + (int) '0');
	dec_to_str(n / 10, fd);
	ft_putchar_fd(print_char, fd);
}

// int	main()
// {
// 	ft_putnbr_fd(2147483647, STDOUT_FILENO);
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// 	ft_putnbr_fd(-2147483648, STDOUT_FILENO);
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// 	ft_putnbr_fd(0, STDOUT_FILENO);
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// 	ft_putnbr_fd(100, STDOUT_FILENO);
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// 	ft_putnbr_fd(-100, STDOUT_FILENO);
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// }
