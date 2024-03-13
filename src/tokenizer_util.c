/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:07:03 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/13 15:37:11 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	type_meta_chr(char *str);
static int	type_quote(char *str);
static int	is_val(char *str);

int	is_token_type(char *str, int target)
{
	if (target == 'm')
		return (type_meta_chr(str));
	else if (target == 'q')
		return (type_quote(str));
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
