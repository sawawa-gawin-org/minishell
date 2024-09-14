/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:25:30 by saraki            #+#    #+#             */
/*   Updated: 2024/09/13 09:04:20 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"
#include "builtin.h"
#include "minishell.h"
#include "path.h"

static int	run_command(t_callback_parametors *callback_args,
				t_exec_parametors *param, t_callback callback);
static int	pipe_fds(int *out_fd, int *in_fd);
static void	init_signal_by_pid(pid_t pid);

/**
 * Executes a process using the given parameters.
 *
 * @param param The execution parameters for the process.
 * @param callback The callback function to be called after the process
 * execution.
 * @return Returns an integer indicating the success or failure of the
 * process execution.
 */
int	make_each_process(t_exec_parametors *param, t_callback callback)
{
	t_callback_parametors	callback_args;

	callback_args.pipe = param->pipe_list->u_data.pipe_data;
	callback_args.status = 0;
	callback_args.cmd = parse_cmd(param->token_list, callback_args.pipe,
			&(callback_args.status));
	callback_args.path = NULL;
	callback_args.env = param->env;
	callback_args.env_lst = param->env_lst;
	if (callback_args.cmd == NULL)
		return (run_command(&callback_args, param, callback));
	if (*(callback_args.cmd) == NULL)
	{
		free(callback_args.cmd);
		callback_args.cmd = NULL;
		return (run_command(&callback_args, param, callback));
	}
	if (!is_builtin(callback_args.cmd[0]))
		callback_args.path = find_cmd(callback_args.cmd[0], param->env,
				&(callback_args.status));
	return (run_command(&callback_args, param, callback));
}

/**
 * Executes a command.
 *
 * @param callback_args The callback parameters.
 * @return The exit status of the command.
 * @note The reason why `callback_args->cmd` free on the parent process is that
 * the each element of array is allocated as a elements of token_list node. 
 * @bug It should be `waitpid` after `:77` and do not free `callback_args->cmd`
 * and `callback_args->path` on the parent process. Because the child process
 * uses the memory.
 */
static int	run_command(t_callback_parametors *callback_args,
				t_exec_parametors *param, t_callback callback)
{
	size_t		pipe_cnt;
	char		**cmd;

	cmd = callback_args->cmd;
	pipe_cnt = doub_lstcnt(param->pipe_list->u_data.pipe_data->head_node);
	if (cmd != NULL && is_builtin(cmd[0]) && pipe_cnt == 1)
		callback_args->status = call_builtin(
				cmd, (void **) param->env_lst, IS_MAIN_PROCESS);
	callback_args->pipe->pids = fork();
	init_signal_by_pid(callback_args->pipe->pids);
	if (callback_args->pipe->pids == 0)
		callback(callback_args);
	if (cmd != NULL && cmd[0] != NULL && ft_strcmp(cmd[0], "exit") == 0
		&& pipe_cnt == 1)
		param->is_exit_called = 1;
	if (callback_args->path != NULL)
		free(callback_args->path);
	if (callback_args->cmd != NULL)
		free(callback_args->cmd);
	if (callback_args->pipe->pids < 0)
		return (GENERAL_ERR);
	return (OK);
}

static void	init_signal_by_pid(pid_t pid)
{
	if (pid == 0)
		init_signal(SIG_DFL, SIG_DFL);
	else
		init_signal(SIG_IGN, SIG_IGN);
}

int	init_pipeline(t_pipelst *pipe_node)
{
	t_pipex	*pipe;
	t_pipex	*next_pipe;

	while (pipe_node->u_data.pipe_data != NULL)
	{
		pipe = (t_pipex *) pipe_node->u_data.pipe_data;
		if (pipe_node->next->u_data.pipe_data != NULL)
		{
			next_pipe = pipe_node->next->u_data.pipe_data;
			if (pipe_fds(&next_pipe->pipe_out_fd, &pipe->pipe_in_fd))
				return (ERR);
		}
		pipe_node = pipe_node->next;
	}
	return (OK);
}

static int	pipe_fds(int *out_fd, int *in_fd)
{
	int	pipe_fd[2];

	pipe_fd[0] = *out_fd;
	pipe_fd[1] = *in_fd;
	if (pipe(pipe_fd) < 0)
		return (ERR);
	*out_fd = pipe_fd[0];
	*in_fd = pipe_fd[1];
	return (OK);
}
