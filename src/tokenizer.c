/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:40:15 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/08 12:44:45 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	tokenizer(char *token_str)
{
	int	type;
	int	len;

	len = ft_strlen(token_str);
	type = detect_redirect(token_str, len);
	if (type > 0)
		return (type);
	
	return (token);
}

int	detect_redirect(char *str, int len)
{
	if (len == 2)
	{
		if (str[0] == '<' && str[1] == '<')
			return (heredoc);
		else if (str[0] == '>' && str[1] == '>')
			return (append);
	}
	else if (len == 1)
	{
		if (str[0] == '<')
			return (less);
		else if (str[0] == '>')
			return (great);
		else if (str[0] == '|')
			return (tube);
	}
	return (token);
}

int	detect_quote(char *str, int len)
{
	if (str[0] == '"' && str[len - 1] == '"')
	{
		if ()
	}
}
