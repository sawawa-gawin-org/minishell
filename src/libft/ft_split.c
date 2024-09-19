/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:29:42 by saraki            #+#    #+#             */
/*   Updated: 2023/08/22 22:42:31 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		total_words(char const *str, char sep);
static unsigned int	set_words(char **result, char const *str,
						char sep, size_t words);
static void			free_untill_index(char **result, size_t index);

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	words;
	size_t	free_index;

	words = total_words(s, c);
	result = (char **) ft_calloc(sizeof(char *), words + 1);
	if (result == NULL)
		return (NULL);
	if (words == 0)
		return (result);
	free_index = set_words(result, s, c, words);
	if (free_index)
	{
		free_untill_index(result, free_index - 1);
		return (NULL);
	}
	return (result);
}

static unsigned int	set_words(char **result, char const *str,
						char sep, size_t words)
{
	unsigned int	start;
	size_t			i_str;
	size_t			index_words;

	start = 0;
	while (*(str + start) == sep)
		start ++;
	i_str = 0;
	index_words = 0;
	while (index_words < words)
	{
		while (str[start + i_str] != sep && str[start + i_str] != '\0')
			i_str ++;
		result[index_words] = ft_substr(str, start, i_str);
		if (result[index_words] == NULL)
			return (index_words + 1);
		while (str[start + i_str] == sep && str[start + i_str] != '\0')
			i_str ++;
		start += i_str;
		i_str = 0;
		index_words ++;
	}
	return (0);
}

static size_t	total_words(char const *str, char sep)
{
	unsigned int	start;
	unsigned int	end;
	size_t			words;

	if (str == NULL || ft_strlen(str) == 0)
		return (0);
	start = 0;
	while (str[start] == sep)
		start ++;
	end = ft_strlen(str) - 1;
	while (str[end] == sep && end > 0)
		end --;
	words = 0;
	while (start <= end)
	{
		if (str[start] != '\0')
			words ++;
		while (str[start] != sep && str[start] != '\0')
			start ++;
		while (str[start] == sep && str[start] != '\0')
			start ++;
	}
	return (words);
}

static void	free_untill_index(char **result, size_t index)
{
	unsigned int	i;

	i = 0;
	while (i < index)
	{
		free(result[i]);
		i ++;
	}
	free(result);
	return ;
}
