/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:57:50 by saraki            #+#    #+#             */
/*   Updated: 2024/06/12 12:15:33 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	with_heredoc_history(char *line, char *heredoc_gained_str);

int	add_history_wraper(char *line, char *heredoc_gained)
{
	int	err;

	err = 0;
	if (heredoc_gained == NULL || *heredoc_gained == '\0')
	{
		add_history(line);
		free(line);
		return (0);
	}
	else
		err = with_heredoc_history(line, heredoc_gained);
	free(heredoc_gained);
	if (err)
		return (-1);
	return (0);
}

static int	with_heredoc_history(char *line, char *heredoc_gained_str)
{
	char	*line_with_nl;
	char	*joined_str;

	line_with_nl = ft_strjoin(line, "\n");
	free(line);
	if (line_with_nl == NULL)
		return (-1);
	joined_str = ft_strjoin(line_with_nl, heredoc_gained_str);
	free(line_with_nl);
	if (line_with_nl == NULL)
		return (-1);
	add_history(joined_str);
	free(joined_str);
	return (0);
}
