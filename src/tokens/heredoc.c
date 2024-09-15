/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:41:27 by syamasaw          #+#    #+#             */
/*   Updated: 2024/09/15 02:49:01 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"
#include "minishell.h"

static void	delete_delimiter_blank(t_blst **delim_nodes);
static int	set_heredoc_string_to_node(t_token_data *delimiter_node);
static char	*append_newline(char *history_str, char *line);
static char	*read_heredoc_lines(char *delimiter);

/**
 * Parses the heredoc tokens.
 *
 * @param tokens_lst A pointer to the list of tokens.
 * @return An integer indicating the success or failure of the parsing process.
 */
int	parse_heredoc(t_blst **tokens_lst)
{
	t_blst			*now_node;
	t_blst			*delim_nodes;
	t_token_data	*data;
	int				err;

	now_node = *tokens_lst;
	while (now_node->u_data.token_data != NULL)
	{
		data = now_node->u_data.token_data;
		if (data->token_type == HEREDOC_FLAG)
		{
			delim_nodes = now_node->next;
			delete_delimiter_blank(&delim_nodes);
			err = concat_tokens_node(&delim_nodes);
			if (err == ERR)
				return (err);
			err = set_heredoc_string_to_node(delim_nodes->u_data.token_data);
			if (err == ERR || err == ERR_SIGINT)
				return (err);
			now_node = now_node->next;
		}
		now_node = now_node->next;
	}
	return (OK);
}

static void	delete_delimiter_blank(t_blst **delim_nodes)
{
	t_blst			*base_node;
	t_token_data	*data;

	base_node = (*delim_nodes)->prev;
	while ((*delim_nodes)->u_data.token_data != NULL
		&& (*delim_nodes)->u_data.token_data->token_type != META_FLAG)
	{
		data = (*delim_nodes)->u_data.token_data;
		if (data->token_type == SPACE_FLAG)
			purge_token_node(delim_nodes);
		else
			(*delim_nodes) = (*delim_nodes)->next;
	}
	*delim_nodes = base_node->next;
	return ;
}

static int	set_heredoc_string_to_node(t_token_data *delimiter_node)
{
	char	*lines;

	init_signal(handler_for_heredoc_readline, SIG_IGN);
	init_rl_for_heredoc();
	lines = read_heredoc_lines(delimiter_node->token_str);
	if (lines == NULL)
		return (ERR);
	if (g_signal != 0)
	{
		if (lines != NULL)
			free(lines);
		return (ERR_SIGINT);
	}
	free(delimiter_node->token_str);
	delimiter_node->token_str = lines;
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
