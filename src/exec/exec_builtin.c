/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 02:39:45 by syamasaw          #+#    #+#             */
/*   Updated: 2024-07-15 02:39:45 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

int	exec_builtin_no_pipe(t_exec_parametors *param, t_blst **envlst)
{
	char		**cmd;
	t_pipex		*pipe;
	t_tokenlst	*node;
	int			result;

	pipe = param->pipe_list->u_data.pipe_data;
	node = shift_token_section(param->token_list, pipe->index);
	cmd = parse_cmd(param, &node, pipe);
	if (cmd == NULL)
		return (ERR_ALLOCATE_MEMORY);
	result = exec_builtin(cmd, envlst);
	free(cmd);
	return (result);
}

int	exec_builtin(char **cmd, t_blst **envlst)
{
	if (ft_strcmp(cmd[0], "export") == 0)
		return (builtin_export(cmd, envlst));
	return (CMD_NOT_FOUND);
}
