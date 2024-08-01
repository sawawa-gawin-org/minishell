/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_processes_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:25:30 by saraki            #+#    #+#             */
/*   Updated: 2024/08/01 18:38:17 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"
#include "builtin.h"

static int	run_command(t_callback_parametors *callback_args,
				t_exec_parametors *param, t_callback callback);

int	make_process(t_exec_parametors *param, t_callback callback)
{
	t_callback_parametors	callback_args;
	t_tokenlst				*start_node;

	callback_args.pipe = param->pipe_list->u_data.pipe_data;
	start_node = shift_token_section(
			param->token_list, callback_args.pipe->index);
	callback_args.cmd = parse_cmd(&start_node, callback_args.pipe);
	if (callback_args.cmd == NULL)
		return (ERR_ALLOCATE_MEMORY);
	callback_args.status = 0;
	callback_args.path = NULL;
	callback_args.env = param->env;
	callback_args.env_lst = param->env_lst;
	if (!is_builtin(callback_args.cmd[0]))
	{
		callback_args.path = find_cmd(callback_args.cmd[0], param->env,
				&(callback_args.status));
		if (!callback_args.path && callback_args.status == CMD_NOT_FOUND)
			cmdnotfound_error(callback_args.cmd[0]);
		else if (!callback_args.path && callback_args.status == CMD_CNT_EXECUTE)
			cmdnotexecutable_error(callback_args.cmd[0]);
	}
	return (run_command(&callback_args, param, callback));
}

static int	run_command(t_callback_parametors *callback_args,
				t_exec_parametors *param, t_callback callback)
{
	size_t		pipe_cnt;
	char		**cmd;

	cmd = callback_args->cmd;
	pipe_cnt = doub_lstcnt(param->pipe_list);
	if (is_builtin(cmd[0]) && pipe_cnt == 1)
		callback_args->status = call_builtin(
				cmd, (void **) param->env_lst, IS_MAIN_PROCESS);
	callback_args->pipe->pids = fork();
	if (callback_args->pipe->pids == 0)
		callback(callback_args);
	free(callback_args->cmd);
	if (callback_args->path != NULL)
		free(callback_args->path);
	if (callback_args->pipe->pids < 0)
		return (GENERAL_ERR);
	return (OK);
}

t_tokenlst	*shift_token_section(t_tokenlst *token_head_node, int index)
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
