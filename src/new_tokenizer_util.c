/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokenizer_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:07:03 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/27 16:51:10 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static size_t	detect_token_len(char *line, int target_type);
static int		detect_token_type(char *token_str, int *type);
static void		detect_meta_token_type(char *meta_token_str, int *type);
static int		is_val(char *str);

char	*allocate_next_token(char **line, int *next_token_type)
{
	char	*token_str;
	int		token_len;

	if (next_token_type == NULL)
		return (NULL);
	if (ft_strchr("<>|", **line) != NULL)
		*next_token_type = META_CHAR;
	else if (ft_strchr("\'\"", **line) != NULL)
		*next_token_type = QUOTE_CHAR;
	else if (is_blank(**line) == 0)
		*next_token_type = WORD_CHAR;
	else
		*next_token_type = BLANK_CHAR;
	token_len = detect_token_len(*line, *next_token_type);
	if (token_len == -1)
		return (NULL);
	token_str = ft_substr(*line, 0, token_len);
	if (token_str == NULL)
		return (NULL);
	if (detect_token_type(token_str, next_token_type))
		return (NULL);
	*line += token_len;
	return (token_str);
}

static size_t	detect_token_len(char *line, int target_type)
{
	size_t	len;

	len = 1;
	if (target_type == META_CHAR && line[0] != '|' && line[0] == line[len])
		len = 2;
	else if (target_type == QUOTE_CHAR)
	{
		while (line[0] != '\0' && line[0] != line[len])
			len++;
		if (line[len] == '\'' || line[len] == '"')
			len += 1;
	}
	else if (target_type == WORD_CHAR)
	{
		len = 0;
		while (line[0] != '\0' && ft_strchr("<>|\"\'", line[len]) == NULL
			&& is_blank(line[len]) == 0)
			len++;
	}
	else if (target_type == BLANK_CHAR)
		len = skip_blank(line, index);
	return (len);
}

static int	detect_token_type(char *token_str, int *type)
{
	size_t	len;
	int		is_closed;

	len = ft_strlen(token_str);
	is_closed = token_str[0] == token_str[len - 1];
	if (*type == META_CHAR)
		detect_meta_token_type(token_str, type);
	else if (*type == QUOTE_CHAR)
	{
		if (len >= 2 && token_str[0] == '\"' && is_closed && is_val(token_str))
			*type = DOUBLE_QUOTE_VAL_FLAG;
		else if (len >= 2 && token_str[0] == '\"' && is_closed)
			*type = DOUBLE_QUOTE_VAL_FLAG;
		else if (len >= 2 && token_str[0] == '\'' && is_closed)
			*type = SINGLE_QUOTE_FLAG;
		else if (token_str[0] == '\'')
			*type = OPEN_QUOTE_FLAG;
	}
	else if (*type == WORD_CHAR && is_val(token_str))
		*type = VAL_FLAG;
	else if (*type == BLANK_CHAR)
		*type = SPACE_FLAG;
	else
		*type = TOKEN_FLAG;
	return (-1);
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
static int	is_val(char *str)
{
	char	*p;

	p = ft_strchr(str, '$');
	if (p != NULL && p[1] != ' ' && p[1] != '\0')
		return (1);
	return (0);
}
