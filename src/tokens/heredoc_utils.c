/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:41:27 by syamasaw          #+#    #+#             */
/*   Updated: 2024/06/09 16:02:58 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static char	*read_heredoc_lines(char *delimiter);
static char	*append_newline(char *history_str, char *line);
static void	update_token_str_data(
				t_token_data *target_data, char *new_token_str);

char	*allocate_heredoc_string_from_input(
			char *delimiter, t_token_data *target_node)
{
	char	*history;
	char	*raw_history;
	char	*new_token_str;

	raw_history = read_heredoc_lines(delimiter);
	if (raw_history == NULL)
		return (NULL);
	new_token_str = ft_strdup(raw_history);
	if (new_token_str == NULL)
	{
		free(raw_history);
		return (NULL);
	}
	history = ft_strjoin(raw_history, delimiter);
	free(raw_history);
	if (history == NULL)
	{
		free(new_token_str);
		return (NULL);
	}
	update_token_str_data(target_node, new_token_str);
	return (history);
}

static char	*read_heredoc_lines(char *delimiter)
{
	char	*line;
	char	*all_lines;

	all_lines = ft_strdup("");
	if (all_lines == NULL)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || g_signal != 0)
			break ;
		else if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		all_lines = append_newline(all_lines, line);
		free(line);
		if (all_lines == NULL)
			break ;
	}
	return (all_lines);
}

char	*allocate_heredoc_string_from_history(
			char *delimiter, t_token_data *target_node)
{
	char	*history;
	char	*new_token_str;
	size_t	new_token_len;
	char	*last_input;

	last_input = target_node->token_str + ft_strlen(delimiter) + 1;
	new_token_len = ft_strlen(last_input) - (ft_strlen(delimiter) + 1); // 長さ要確認
	new_token_str = ft_substr(target_node->token_str,
			ft_strlen(delimiter) + 1, new_token_len);
	if (new_token_str == NULL)
		return (NULL);
	history = ft_strdup("");
	if (history == NULL)
	{
		free(new_token_str);
		return (NULL);
	}
	update_token_str_data(target_node, new_token_str);
	return (history);
}

static void	update_token_str_data(
				t_token_data *target_data, char *new_token_str)
{
	int		type;	

	type = is_flag(new_token_str, target_data->token_type); // TMP
	free(target_data->token_str);
	target_data->token_str = new_token_str;
	target_data->token_type = type;
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
