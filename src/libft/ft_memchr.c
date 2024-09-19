/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:52:36 by saraki            #+#    #+#             */
/*   Updated: 2023/08/22 15:34:25 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	target;

	target = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == target)
			return ((void *)(s + i));
		i ++;
	}
	return (NULL);
}
