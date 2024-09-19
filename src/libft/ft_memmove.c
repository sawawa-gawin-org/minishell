/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 05:33:07 by saraki            #+#    #+#             */
/*   Updated: 2023/09/25 17:31:06 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*u_dest;
	unsigned char	*u_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	u_dest = (unsigned char *) dest;
	u_src = (unsigned char *) src;
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else
	{
		i = n;
		while (i > 0)
		{
			u_dest[i - 1] = u_src[i - 1];
			i --;
		}
		return (dest);
	}
}
