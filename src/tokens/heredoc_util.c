/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_from_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:42:12 by saraki            #+#    #+#             */
/*   Updated: 2024/06/13 17:24:47 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"
#include "minishell.h"

static char	*append_newline(char *history_str, char *line);
static char	*read_heredoc_lines(char *delimiter);

int	set_heredoc_string_to_node(
		char *delimiter, t_token_data *target_node)
{
	char	*lines;
	char	*new_token_str;

	init_signal(handler_for_heredoc_readline, SIG_IGN);
	init_rl_for_heredoc();
	lines = read_heredoc_lines(delimiter);
	if (lines == NULL)
		return (ERR);
	if (g_signal != 0)
	{
		if (lines != NULL)
			free(lines);
		return (ERR_SIGINT);
	}
	new_token_str = ft_strdup(lines);
	if (new_token_str == NULL)
	{
		free(lines);
		return (ERR);
	}
	free(lines);
	update_token_str_data(target_node, new_token_str);
	return (OK);
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
		if (line == NULL && g_signal == 0)
			ft_putstr_fd("\n", 2);
		if (line == NULL || g_signal != 0)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		all_lines = append_newline(all_lines, line);
		free(line);
		if (all_lines == NULL)
			break ;
	}
	if (line != NULL)
		free(line);
	return (all_lines);
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

void	update_token_str_data(
				t_token_data *target_data, char *new_token_str)
{
	int		type;	

	type = is_flag(new_token_str, target_data->token_type);
	free(target_data->token_str);
	target_data->token_str = new_token_str;
	target_data->token_type = type;
}

//data->token_typeとheredoc_strから、"$VAL"か'VAL'か"VAL"かを判断して、FLAGを割り当てる
// Need fix
int	is_flag(char *heredoc_str, int type) // Check later
{
	if (type == SINGLE_QUOTE_FLAG)
		return (SINGLE_QUOTE_FLAG);
	else
	{
		if (is_val(heredoc_str))
			return (DOUBLE_QUOTE_VAL_FLAG);
		else
			return (DOUBLE_QUOTE_FLAG);
	}
}
