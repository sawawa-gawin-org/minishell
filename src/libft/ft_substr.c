/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:19:02 by saraki            #+#    #+#             */
/*   Updated: 2023/09/29 16:01:09 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		start = s_len;
	if (s_len - start < len)
		len = s_len - start;
	result = (char *) ft_calloc(sizeof(char), len + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcat(result, s + start, len + 1);
	return (result);
}

// #include <stdio.h>
// int main()
// {
// 	char	*result = ft_substr("H2", 2, 4);
// 	printf("%s\n", result);
// 	free(result);
// 	result = NULL;
// 	result = ft_substr("Hello World", 6, 5);
// 	printf("%s\n", result);
// 	free(result);
// 	result = NULL;
// 	result = ft_substr("Hello World", 6, 100);
// 	printf("%s\n", result);
// 	free(result);
// 	result = NULL;
// 	result = ft_substr("Hello World", 6, 0);
// 	printf("%s\n", result);
// 	free(result);
// 	result = NULL;
// 	result = ft_substr("Hello World", 100, 3);
// 	printf("%s\n", result);
// 	free(result);
// 	result = NULL;
// }
