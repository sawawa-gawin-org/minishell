/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_processes_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:25:30 by saraki            #+#    #+#             */
/*   Updated: 2024/05/15 07:24:03 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static char			**convert_tokenlst_to_char_array(
						t_tokenlst *section_start_node);
static t_tokenlst	*shift_token_section(
						t_tokenlst *token_head_node, int index);

int	make_process(
	t_tokenlst *token_head_node,
	t_pipelst *pipe_head_node,
	t_callback callback)
{
	char		**cmd;
	char		*path;
	t_pipex		*pipe;
	t_tokenlst	*section_start_node;

	pipe = (t_pipex *)pipe_head_node->u_data.pipe_data;
	section_start_node = shift_token_section(token_head_node, pipe->index);
	cmd = convert_tokenlst_to_char_array(section_start_node);
	if (cmd == NULL)
		return (ERR);
	path = find_cmd(section_start_node->u_data.str);
	if (!path)
	{
		free(cmd);
		return (ERR);
	}
	pipe->pids = fork();
	if (pipe->pids == 0)
		callback(cmd, path, pipe);
	free(cmd);
	free(path);
	if (pipe->pids < 0)
		return (ERR);
	return (OK);
}

static char	**convert_tokenlst_to_char_array(
				t_tokenlst *section_start_node)
{
	int			i;
	int			size;
	t_tokenlst	*now_node;
	char		**cmd;

	size = 0;
	now_node = section_start_node;
	while (now_node->u_data.str != NULL
		&& ft_strcmp(now_node->u_data.str, "|"))
	{
		size ++;
		now_node = now_node->next;
	}
	cmd = (char **)malloc(sizeof(char *) * (size + 1));
	if (cmd == NULL)
		return (NULL);
	i = 0;
	now_node = section_start_node;
	while (i < size && now_node->u_data.str != NULL)
	{
		cmd[i] = now_node->u_data.str;
		now_node = now_node->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

static t_tokenlst	*shift_token_section(
						t_tokenlst *token_head_node, int index)
{
	int			i;
	t_tokenlst	*section_start_node;

	i = 0;
	section_start_node = token_head_node;
	while (i < index && section_start_node->u_data.str != NULL)
	{
		section_start_node = section_start_node->next;
		if (ft_strcmp(section_start_node->u_data.str, "|") == 0)
		{
			i++;
			section_start_node = section_start_node->next;
		}
	}
	return (section_start_node);
}
