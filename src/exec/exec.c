/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:22:09 by saraki            #+#    #+#             */
/*   Updated: 2024/04/05 04:31:02 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static t_pipelst	*init_pipe_lst(t_tokenlst	*token_head_node);
static t_pipelst	*init_pipe_node(int index);
static void			close_fds_all(t_pipelst *pipe_head_node);

// # about token_head_node
// `token_head_node` is a linked list that stores the command line.
// exapmle:
// token_head_node->data = "ls"
// token_head_node->next->data = "-l"
// token_head_node->next->next->data = "|"
// token_head_node->next->next->next->data = "wc"
// token_head_node->next->next->next->next->data = "-l"

int	exec(t_tokenlst *token_head_node)
{
	t_pipelst	*pipe_head_node;

	if (token_head_node == NULL)
		return (1);
	pipe_head_node = init_pipe_lst(token_head_node);
	if (pipe_head_node == NULL)
		return (1);
	make_processes(token_head_node, pipe_head_node);
	close_fds_all(pipe_head_node);
	doub_lstdelall((void **)&pipe_head_node, free);
	return (0);
}

static t_pipelst	*init_pipe_lst(t_tokenlst	*token_head_node)
{
	int			index;
	t_pipelst	*pipe_head_node;
	t_pipelst	*new_node;

	index = 0;
	pipe_head_node = doub_lstnew(NULL);
	while (pipe_head_node != NULL && token_head_node->data != NULL)
	{
		new_node = init_pipe_node(index);
		if (new_node == NULL)
		{
			doub_lstdelall((void **)&pipe_head_node, free);
			return (NULL);
		}
		doub_lstappend((void **)&pipe_head_node, new_node);
		((t_pipex *) (new_node->data))->head_node = pipe_head_node;
		while (!ft_strcmp((char *)token_head_node->data, "|"))
			token_head_node = token_head_node->next;
		token_head_node = token_head_node->next;
	}
	return (pipe_head_node);
}

static t_pipelst	*init_pipe_node(int index)
{
	t_pipelst	*node;
	t_pipex		*pipedata;

	pipedata = (t_pipex *)malloc(sizeof(t_pipex));
	if (pipedata == NULL)
		return (NULL);
	pipedata->in_fd = -1;
	pipedata->out_fd = -1;
	pipedata->pipe_in_fd = -1;
	pipedata->pipe_out_fd = -1;
	pipedata->index = index;
	pipedata->pids = 0;
	node = (t_pipelst *)doub_lstnew((void *)pipedata);
	if (node == NULL)
	{
		free(pipedata);
		return (NULL);
	}
	return (node);
}

static void	close_fds_all(t_pipelst *pipe_head_node)
{
	t_pipex	*pipe;
	t_pipelst *now_node;

	now_node = pipe_head_node;
	while (now_node->data != NULL)
	{
		pipe = (t_pipex *)now_node->data;
		if (pipe->in_fd >= 0)
			close(pipe->in_fd);
		if (pipe->out_fd >= 0)
			close(pipe->out_fd);
		if (pipe->pipe_in_fd >= 0)
			close(pipe->pipe_in_fd);
		if (pipe->pipe_out_fd >= 0)
			close(pipe->pipe_out_fd);
	}
}
