/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:57:50 by saraki            #+#    #+#             */
/*   Updated: 2024/06/12 13:28:34 by saraki           ###   ########.fr       */
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
		return (OK);
	}
	else
		err = with_heredoc_history(line, heredoc_gained);
	if (err)
		return (ERR);
	return (OK);
}

static int	with_heredoc_history(char *line, char *heredoc_gained_str)
{
	char	*line_with_nl;
	char	*joined_str;

	line_with_nl = ft_strjoin(line, "\n");
	if (line_with_nl == NULL)
		return (ERR);
	joined_str = ft_strjoin(line_with_nl, heredoc_gained_str);
	free(line_with_nl);
	if (joined_str == NULL)
		return (ERR);
	add_history(joined_str);
	free(joined_str);
	return (OK);
}
