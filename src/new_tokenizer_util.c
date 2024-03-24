/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokenizer_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:07:03 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/24 05:56:07 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	detect_token_len(char *line, int *target_type);
static int	type_meta_chr(char *str);
static int	type_quote(char *str);
static int	is_val(char *str);

char *allocate_next_token(char **line, int *next_token_type)
{
	char	*token_str;
	int		token_len;

	if (next_token_type == NULL)
		return (NULL);
	if (ft_strchr("<>|", **line) != NULL)
		*next_token_type = LESS_FLAG | GREAT_FLAG | TUBE_FLAG | HEREDOC_FLAG | APPEND_FLAG;
	else if (ft_strchr("\'\"", **line) != NULL)
		*next_token_type = OPEN_QUOTE_FLAG | SINGLE_QUOTE_FLAG | DOUBLE_QUOTE_VAL_FLAG | DOUBLE_QUOTE_FLAG | OPEN_QUOTE_FLAG | TOKEN_FLAG;
	else if (is_blank(**line) == 0)
		*next_token_type = VAL_FLAG | TOKEN_FLAG;
	else
		*next_token_type = SPACE_FLAG;
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

static int	detect_token_len(char *line, int target_type)
{
	int	len;

	len = 1;
	if (target_type == LESS_FLAG | GREAT_FLAG | TUBE_FLAG | HEREDOC_FLAG | APPEND_FLAG)
	{
		if (line[len] != '|' && line[len] == line[len + 1])
			len = 2;
	}
	else if (target_type == OPEN_QUOTE_FLAG | SINGLE_QUOTE_FLAG | DOUBLE_QUOTE_VAL_FLAG | DOUBLE_QUOTE_FLAG | OPEN_QUOTE_FLAG | TOKEN_FLAG)
	{
		while (line[len] != '\0' && line[0] != line[len])
			len++;
		if (line[len] == '\'' || line[len] == '"')
			len += 1;
	}
	else if (target_type = VAL_FLAG | TOKEN_FLAG)
	{
		len = 0;
		while (line[len] != '\0' && ft_strchr("<>|\"\'", line[len]) == NULL && is_blank(line[len]) == 0)
			len++;
	}
	else if (target_type = SPACE_FLAG)
		len = skip_blank(line, index);
	return (len);
}

static int	detect_token_type(char *token_str, int *target_type)
{
	if (*target_type == LESS_FLAG | GREAT_FLAG | TUBE_FLAG | HEREDOC_FLAG | APPEND_FLAG)
	{
		if (*token_str == '|')
			*target_type = TUBE_FLAG;
		else if (*token_str == '<')
			*target_type = LESS_FLAG | HEREDOC_FLAG;
		else if (*token_str == '>')
			*target_type = GREAT_FLAG | APPEND_FLAG;
	}
	else if (*target_type == OPEN_QUOTE_FLAG | SINGLE_QUOTE_FLAG | DOUBLE_QUOTE_VAL_FLAG | DOUBLE_QUOTE_FLAG | OPEN_QUOTE_FLAG | TOKEN_FLAG)
	{

	}
	else if (*target_type = VAL_FLAG | TOKEN_FLAG)
	{

	}

	
	if (target == 'm')
		return (type_meta_chr(str));
	else if (target == 'q')
		return (type_quote(str));
	else if (target == 'b')
		return (space);
	else if (target == 'w')
	{
		if (is_val(str))
			return (val);
		else
			return (token);
	}
	return (-1);
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
	*tokens = lstadd_token(*tokens, str, type);
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
		while (line[index + len] != '\0' && ft_strchr("<>|\"\'", line[index \
			+ len]) == NULL && is_blank(line[len + index]) == 0)
			len++;
	}
	else if (target == 'b')
		len = skip_blank(line, index);
	return (len);
}

int	is_token_type(char *str, int target)
{
	if (target == 'm')
		return (type_meta_chr(str));
	else if (target == 'q')
		return (type_quote(str));
	else if (target == 'b')
		return (space);
	else if (target == 'w')
	{
		if (is_val(str))
			return (val);
		else
			return (token);
	}
	return (-1);
}

static int	type_meta_chr(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 1)
	{
		if (str[0] == '|')
			return (tube);
		else if (str[0] == '<')
			return (less);
		else if (str[0] == '>')
			return (great);
	}
	else if (len == 2)
	{
		if (str[0] == '<' && str[0] == str[1])
			return (heredoc);
		else if (str[0] == '>' && str[0] == str[1])
			return (append);
	}
	return (0);
}

static int	type_quote(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 2)
		return (open_quote);
	if (str[0] == '\'' && str[0] == str[len - 1])
		return (single_quote);
	else if (str[0] == '\"' && str[0] == str[len - 1])
	{
		if (is_val(str))
			return (double_quote_val);
		else
			return (double_quote);
	}
	else
		return (open_quote);
	return (token);
}

static int	is_val(char *str)
{
	char	*p;

	p = ft_strchr(str, '$');
	if (p != NULL && p[1] != ' ' && p[1] != '\0') //$のあとがスペースやヌルだけでなく、予約語が来るのはよくない？
		return (1);
	return (0);
}
