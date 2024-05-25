/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:41:27 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/25 21:23:53 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static char	*append_newline(char *history_str, char *line);

char	*get_heredoc_input(char *delimiter) // FIX: #81
{
	char	*line;
	char	*all_line;

	all_line = (char *)ft_calloc(1, sizeof(char));
	if (all_line == NULL)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || g_signal != 0)
		{
			break ;
		}
		else if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		all_line = append_newline(all_line, line);
		free(line);
		if (all_line == NULL)
			break ;
	}
	return (all_line);
}

static char	*append_newline(char *all_line, char *line)
{
	char	*ret;
	char	*ret_with_nl;

	ret = ft_strjoin(all_line, line);
	free(all_line);
	if (ret == NULL)
		return (NULL);
	ret_with_nl = ft_strjoin(ret, "\n");
	free(ret);
	if (ret_with_nl == NULL)
		return (NULL);	
	return (ret_with_nl);
}
