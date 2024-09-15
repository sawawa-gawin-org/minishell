/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bridge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:24:11 by saraki            #+#    #+#             */
/*   Updated: 2024/09/15 09:36:23 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"
#include "common.h"
#include "env.h"
#include "dbllst.h"

/**
 * Executes the commands in the given tokens list.
 *
 * @param tokens_lst The list of tokens representing the commands.
 * @param env_lst    The list of environment variables.
 * @param status     A pointer to the status variable.
 * @return           Returns an integer indicating the execution status.
 */
int	exec_tokenslst_cmds(t_blst *tokens_lst, t_blst **env_lst, int *status)
{
	char	**env;

	env = create_env_arr_from_lst(*env_lst, 0);
	if (env == NULL)
		return (ERR);
	*status = exec((t_tokenlst **) &tokens_lst, env, env_lst);
	free_environment_array(env);
	return (OK);
}
