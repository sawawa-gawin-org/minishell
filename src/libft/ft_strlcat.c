/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:29:17 by saraki            #+#    #+#             */
/*   Updated: 2023/09/25 17:48:52 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dst_len = 0;
	src_len = ft_strlen(src);
	if (dst != NULL)
		dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + src_len);
	i = 0;
	j = dst_len;
	while (i < size - dst_len - 1 && src[i] != '\0')
	{
		dst[j] = src[i];
		i ++;
		j ++;
	}
	dst[j] = '\0';
	return (dst_len + src_len);
}
