/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 07:07:07 by saraki            #+#    #+#             */
/*   Updated: 2023/09/27 17:42:25 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *) big);
	if (len == 0)
		return (0);
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	if (len < little_len)
		return (NULL);
	i = 0;
	while (i < len - little_len + 1 && big[i] != '\0')
	{
		if (big[i] == little[0] && !ft_strncmp(big + i, little, little_len))
			return ((char *) big + i);
		i ++;
	}
	return (NULL);
}
