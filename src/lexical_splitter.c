/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:28:52 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/05 15:04:38 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		get_token_redirect(char *line, t_token **tokens, int index);
int		get_token_quote(char *line, t_token **tokens, int index);
int		get_token_normal(char *line, t_token **tokens, int index);

t_token	*lexical_splitter(char *line, t_token *tokens)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_strchr("<>|", line[i]) != NULL)
		{
			i += get_token_redirect(line, &tokens, i);
		}
		else if (ft_strchr("\'\"", line[i]) != NULL)
		{
			i += get_token_quote(line, &tokens, i);
		}
		else if (line[i] != ' ')
		{
			i += get_token_normal(line, &tokens, i);
		}
		if (line[i] == ' ')
			i++;
	}
	return (tokens);
}

int	get_token_redirect(char *line, t_token **tokens, int index)
{
	char	*str;
	int		pos;

	str = NULL;
	pos = 1;
	if (line[index] != '|' && line[index] == line[index + 1])
		pos = 2;
	str = ft_substr(line, index, pos);
	*tokens = lstnew_2way(*tokens, str);
	free(str);
	return (pos);
}

int	get_token_quote(char *line, t_token **tokens, int index)
{
	char	*str;
	int		pos;

	str = NULL;
	pos = 1;
	while (line[index + pos] != '\0' && line[index] != line[index + pos])
		pos++;
	if (line[index + pos] == '\'' || line[index + pos] == '"')
		pos += 1;
	str = ft_substr(line, index, pos);
	*tokens = lstnew_2way(*tokens, str);
	free(str);
	return (pos);
}

int	get_token_normal(char *line, t_token **tokens, int index)
{
	char	*str;
	int		pos;

	str = NULL;
	pos = 0;
	while (line[index + pos] != '\0' && ft_strchr(" <>|", line[index \
			+ pos]) == NULL)
		pos++;
	str = ft_substr(line, index, pos);
	*tokens = lstnew_2way(*tokens, str);
	free(str);
	return (pos);
}
