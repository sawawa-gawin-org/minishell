/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:30:21 by saraki            #+#    #+#             */
/*   Updated: 2024/08/31 18:45:10 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Joins two strings with a specified separator.
 *
 * This function takes two strings, `str1` and `str2`, and concatenates them
 * together with the specified separator `sep`.
 * The resulting string is returned.
 *
 * @param str1 The first string to be joined.
 * @param str2 The second string to be joined.
 * @param sep The separator character to be used.
 * @return The joined string.
 */
char	*ft_strjoin_with_sep(char *str1, char *str2, char sep)
{
	char	*ret;
	size_t	str1_len;
	size_t	str2_len;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	else if (str1 == NULL && str2 != NULL)
		return (ft_strdup(str2));
	else if (str1 != NULL && str2 == NULL)
		return (ft_strdup(str1));
	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	ret = (char *)malloc(sizeof(char) * (str1_len + str2_len + 2));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, str1, str1_len + 1);
	ret[str1_len] = sep;
	ft_strlcpy(ret + str1_len + 1, str2, str2_len + 1);
	return (ret);
}
