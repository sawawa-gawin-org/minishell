/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:07:03 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/19 22:34:00 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static size_t	detect_token_len(char *line, int target_type);
static void		detect_token_type(char *token_str, int *type);
static void		detect_meta_token_type(char *meta_token_str, int *type);

char	*allocate_next_token(char **line, int *next_token_type)
{
	char	*token_str;
	size_t	token_len;

	if (**line == '\0')
		return (NULL);
	if (next_token_type == NULL)
		return (NULL);
	if (ft_strchr("<>|", **line) != NULL)
		*next_token_type = META_FLAG;
	else if (ft_strchr("\'\"", **line) != NULL)
		*next_token_type = QUOTE_FLAG;
	else if (is_blank(**line) == 0)
		*next_token_type = WORD_FLAG;
	else
		*next_token_type = BLANK_FLAG;
	token_len = detect_token_len(*line, *next_token_type);
	token_str = ft_substr(*line, 0, token_len);
	if (token_str == NULL)
		return (NULL);
	detect_token_type(token_str, next_token_type);
	*line += token_len;
	return (token_str);
}

static size_t	detect_token_len(char *line, int target_type)
{
	size_t	len;

	len = 1;
	if (target_type == META_FLAG && line[0] != '|' && line[0] == line[len]) // bag
		len = 2;
	else if (target_type == QUOTE_FLAG)
	{
		while (line[0] != '\0' && line[0] != line[len])
			len++;
		if (line[len] == '\'' || line[len] == '"')
			len += 1;
	}
	else if (target_type == WORD_FLAG)
	{
		len = 0;
		while (line[0] != '\0' && ft_strchr("<>|\"\'", line[len]) == NULL \
				&& is_blank(line[len]) == 0)
			len++;
	}
	else if (target_type == BLANK_FLAG)
	{
		while (line[len] != '\0' && is_blank(line[len]))
			len++;
	}
	return (len);
}

static void	detect_token_type(char *token_str, int *type)
{
	size_t	len;
	int		is_closed;

	len = ft_strlen(token_str);
	is_closed = token_str[0] == token_str[len - 1];
	if (*type == META_FLAG)
		detect_meta_token_type(token_str, type);
	else if (*type == QUOTE_FLAG)
	{
		if (len >= 2 && token_str[0] == '\"' && is_closed && is_val(token_str))
			*type = DOUBLE_QUOTE_VAL_FLAG;
		else if (len >= 2 && token_str[0] == '\"' && is_closed)
			*type = DOUBLE_QUOTE_FLAG;
		else if (len >= 2 && token_str[0] == '\'' && is_closed)
			*type = SINGLE_QUOTE_FLAG;
		else
			*type = OPEN_QUOTE_FLAG;
	}
	else if (*type == WORD_FLAG && is_val(token_str))
		*type = VAL_FLAG;
	else if (*type == BLANK_FLAG)
		*type = SPACE_FLAG;
	else
		*type = TOKEN_FLAG;
}

static void	detect_meta_token_type(char *meta_token_str, int *type)
{
	size_t	len;

	len = ft_strlen(meta_token_str);
	if (*meta_token_str == '|')
		*type = TUBE_FLAG;
	else if (*meta_token_str == '<')
		*type = LESS_FLAG | HEREDOC_FLAG;
	else if (*meta_token_str == '>')
		*type = GREAT_FLAG | APPEND_FLAG;
	if (len > 1 && meta_token_str[0] == meta_token_str[len - 1])
		*type &= ~(LESS_FLAG | GREAT_FLAG);
	else
		*type &= ~(HEREDOC_FLAG | APPEND_FLAG);
}

//$のあとがスペースやヌルだけでなく、予約語が来るのはよくない？
int	is_val(char *str)
{
	char	*p;

	p = ft_strchr(str, '$');
	if (p != NULL && p[1] != ' ' && p[1] != '\0')
		return (1);
	return (0);
}
