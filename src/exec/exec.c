/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:22:09 by saraki            #+#    #+#             */
/*   Updated: 2024/06/30 01:15:01 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static t_pipelst	*init_pipe_lst(t_tokenlst *token_head_node);
static t_pipelst	*init_pipe_node(int index);
static void			close_fds_all(t_pipelst *pipe_head_node);

// # about token_head_node
// `token_head_node` is a linked list that stores the command line.
// exapmle1:
// token_head_node->data = "ls"
// token_head_node->next->data = "-l"
// token_head_node->next->next->data = "|"
// token_head_node->next->next->next->data = "wc"
// token_head_node->next->next->next->next->data = "-l"
// exapmle2:
// token_head_node->data = "ls"
// token_head_node->next->data = "-l"
// token_head_node->next->next->data = ">"
// token_head_node->next->next->next->data = "out.txt"

/// @brief 
/// @param token_head_node 
/// @param env 
/// @return exit status code
int	exec(t_tokenlst *token_head_node, char **env, t_blst **env_lst)
{
	t_exec_parametors	param;
	int					status;

	param.token_list = token_head_node;
	param.env_lst = env_lst;
	param.env = env;
	param.pipe_list = init_pipe_lst(param.token_list);
	if (param.pipe_list == NULL)
		return (ERR_ALLOCATE_MEMORY);
	if (param.pipe_list->prev->u_data.pipe_data == NULL
		&& param.pipe_list->next->u_data.pipe_data == NULL)
	{
		status = exec_builtin_no_pipe(&param, env_lst);
		if (status != OK)
			status = make_processes(&param);
	}
	else
		status = make_processes(&param);
	close_fds_all(param.pipe_list);
	doub_lstdelall((void **)&param.pipe_list, free);
	return (status);
}

static t_pipelst	*init_pipe_lst(t_tokenlst *token_head_node)
{
	int			index;
	t_pipelst	*pipe_head_node;
	t_pipelst	*new_node;

	index = 0;
	pipe_head_node = doub_lstnew(NULL);
	while (pipe_head_node != NULL && token_head_node->u_data.str != NULL)
	{
		new_node = init_pipe_node(index);
		if (new_node == NULL)
		{
			doub_lstdelall((void **)&pipe_head_node, free);
			return (NULL);
		}
		index ++;
		doub_lstappend((void **)&pipe_head_node, new_node);
		new_node->u_data.pipe_data->head_node = pipe_head_node;
		while (token_head_node->u_data.str != NULL
			&& ft_strcmp((char *)token_head_node->u_data.str, "|"))
			token_head_node = token_head_node->next;
		if (token_head_node->u_data.str == NULL)
			break ;
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
	pipedata->pipe_in_fd = -1;
	pipedata->pipe_out_fd = -1;
	pipedata->file_in_fd = -1;
	pipedata->file_out_fd = -1;
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
	t_pipex		*pipe;
	t_pipelst	*now_node;

	now_node = pipe_head_node;
	while (now_node->u_data.pipe_data != NULL)
	{
		pipe = (t_pipex *)now_node->u_data.pipe_data;
		if (pipe->file_in_fd >= 0)
			close(pipe->file_in_fd);
		if (pipe->file_out_fd >= 0)
			close(pipe->file_out_fd);
		if (pipe->pipe_in_fd >= 0)
			close(pipe->pipe_in_fd);
		if (pipe->pipe_out_fd >= 0)
			close(pipe->pipe_out_fd);
		now_node = now_node->next;
	}
}
