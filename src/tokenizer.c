/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:28:52 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/11 18:24:04 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	add_token(char *line, t_token **tokens, int index, int target);
static int	count_substr_len(char *line, int index, int target);

t_token	*tokenizer(char *line, t_token *tokens)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] != '\0')
	{
		j = 0;
		if (ft_strchr("<>|", line[i]) != NULL)
			j = add_token(line, &tokens, i, 'm');
		else if (ft_strchr("\'\"", line[i]) != NULL)
			j = add_token(line, &tokens, i, 'q');
		else if (line[i] != ' ')
			j = add_token(line, &tokens, i, 'w');
		if (j == -1)
		{
			del_lst(tokens);
			return (NULL);
		}
		if (line[i + j] == ' ')
			j++;
		i += j;
	}
	return (tokens);
}

static int	add_token(char *line, t_token **tokens, int index, int target)
{
	char	*str;
	int		pos;
	int		type;

	str = NULL;
	pos = count_substr_len(line, index, target);
	str = ft_substr(line, index, pos);
	if (!str)
		return (-1);
	type = is_token_type(str, target);
	*tokens = lstnew_2way(*tokens, str, type);
	free(str);
	if (*tokens == NULL)
		return (-1);
	return (pos);
}

static int	count_substr_len(char *line, int index, int target)
{
	int	len;

	len = 1;
	if (target == 'm')
	{
		if (line[index] != '|' && line[index] == line[index + 1])
			len = 2;
	}
	else if (target == 'q')
	{
		while (line[index + len] != '\0' && line[index] != line[index + len])
			len++;
		if (line[index + len] == '\'' || line[index + len] == '"')
			len += 1;
	}
	else if (target == 'w')
	{
		len = 0;
		while (line[index + len] != '\0' && ft_strchr(" <>|\"\'", line[index \
			+ len]) == NULL)
			len++;
	}
	return (len);
}
