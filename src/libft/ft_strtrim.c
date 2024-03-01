/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:00:37 by saraki            #+#    #+#             */
/*   Updated: 2023/09/29 16:02:17 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			is_target(char s, char const *set);
static unsigned int	start_where(const char *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*result;
	unsigned int	start;
	size_t			total_len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = start_where(s1, set);
	total_len = ft_strlen(s1) - start;
	while (total_len > 0)
	{
		if (!is_target(s1[start + total_len - 1], set))
			break ;
		total_len --;
	}
	result = ft_substr(s1, start, total_len);
	if (result == NULL)
		return (NULL);
	return (result);
}

static unsigned int	start_where(const char *s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (is_target(s1[i], set))
		i ++;
	return (i);
}

static int	is_target(char s, char const *set)
{
	while (*set)
	{
		if (s == *set)
			return (1);
		set ++;
	}
	return (0);
}

// #include <stdio.h>
// int main()
// {
// 	char	*result = ft_strtrim("aaabc12c345bba6a7a8abb9accbc", "abc");
// 	printf("%s\n", result);
// 	free(result);
// 	result = ft_strtrim("hello world", "world");
// 	printf("%s\n", result);
// 	free(result);
// 	result = ft_strtrim("", "");
// 	printf("%s\n", result);
// 	free(result);
// }
