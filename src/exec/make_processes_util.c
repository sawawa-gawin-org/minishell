/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_processes_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:25:30 by saraki            #+#    #+#             */
/*   Updated: 2024/05/15 08:30:12 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static t_tokenlst	*shift_token_section(
						t_tokenlst *token_head_node, int index);

int	make_process(
	t_tokenlst *token_head_node,
	t_pipelst *pipe_head_node,
	t_callback callback)
{
	char		**cmd;
	char		*executable_path;
	t_pipex		*pipe;
	t_tokenlst	*start_node;

	pipe = pipe_head_node->u_data.pipe_data;
	start_node = shift_token_section(token_head_node, pipe->index);
	cmd = parse_cmd(start_node, pipe);
	if (cmd == NULL)
		return (ERR);
	executable_path = find_cmd(cmd[0]);
	if (!executable_path)
	{
		free(cmd);
		return (ERR);
	}
	pipe->pids = fork();
	if (pipe->pids == 0)
		callback(cmd, executable_path, pipe);
	free(cmd);
	free(executable_path);
	if (pipe->pids < 0)
		return (ERR);
	return (OK);
}

static t_tokenlst	*shift_token_section(
						t_tokenlst *token_head_node, int index)
{
	int			i;
	t_tokenlst	*node;

	i = 0;
	node = token_head_node;
	while (i < index && node->u_data.str != NULL)
	{
		node = node->next;
		if (ft_strcmp(node->u_data.str, "|") == 0)
		{
			i++;
			node = node->next;
		}
	}
	return (node);
}
