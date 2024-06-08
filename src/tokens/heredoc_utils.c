/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:41:27 by syamasaw          #+#    #+#             */
/*   Updated: 2024/06/08 04:24:14 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static char	*append_newline(char *history_str, char *line);
static char	*get_inline_heredoc_input(char *delimiter, char *token_str);
static char	*append_current_heredoc(
				char *source, t_blst *gain_node, char *delim_str);

char	*get_heredoc_input(char *delimiter, char *token_str)
{
	char	*line;
	char	*all_line;

	if (ft_strcmp(delimiter, token_str) != 0)
		return (get_inline_heredoc_input(delimiter, token_str));
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

static char	*get_inline_heredoc_input(char *delimiter, char *token_str)
{
	char	*token_str_without_dekimiter;
	char	*all_line;
	char	*little;

	little = ft_strjoin(delimiter, "\n");
	if (little == NULL)
		return (NULL);
	token_str_without_dekimiter = ft_strnstr(token_str, little, INT_MAX) + ft_strlen(little);
	free(little);
	if (token_str_without_dekimiter == NULL)
		return (NULL);
	all_line = ft_strdup(token_str_without_dekimiter);
	if (all_line == NULL)
		return (NULL);
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

static char	*append_current_heredoc(
				char *source, t_blst *gain_node, char *delim_str)
{
	char	*ret;
	char	*gain_str;
	size_t	total_len;

	gain_str = gain_node->u_data.t_data->token_str;
	ret = ft_strjoin(ft_strjoin(ft_strjoin(source, gain_str), delim_str), "\n");//2, 3段階目で失敗した時にfree出来ない
	free(source);
	if (ret == NULL)
		return (NULL);
	return (ret);
}