/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:05:16 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/01 10:11:05 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if ((*s == '\0') && ((char)c == '\0'))
			return ((char *)s);
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	sub_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len || len < 1)
	{
		sub = (char *)malloc(1);
		sub[0] = '\0';
		return (sub);
	}
	if (len < s_len - start)
		sub_len = len;
	else
		sub_len = s_len - start;
	sub = (char *)malloc((sub_len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *restrict dest, const char *restrict src, size_t size)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	if (size == 0)
		return (len);
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

char	*ft_strdup(char *src)
{
	char	*copysrc;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	copysrc = (char *)malloc((len + 1) * sizeof(char));
	if (copysrc == NULL)
		return (copysrc);
	while (src[i])
	{
		copysrc[i] = src[i];
		i++;
	}
	copysrc[i] = '\0';
	return (copysrc);
}
