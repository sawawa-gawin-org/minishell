/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 05:17:58 by saraki            #+#    #+#             */
/*   Updated: 2023/09/25 17:34:44 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*u_dest;
	unsigned char	*u_src;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	u_dest = (unsigned char *) dest;
	u_src = (unsigned char *) src;
	while (i < n)
	{
		u_dest[i] = u_src[i];
		i ++;
	}
	return (dest);
}
