/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:32:32 by saraki            #+#    #+#             */
/*   Updated: 2024/08/02 22:17:46 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "dbllst.h"
#include "env.h"

static int	valid_option(char **cmd);
static int	unset_env(char **cmd, t_blst **envlst, int mode);

int	builtin_unset(char **cmd, t_blst **envlst, int mode)
{
	int		status;

	status = valid_option(cmd);
	if (status > 0)
		return (status);
	return (unset_env(cmd, envlst, mode));
}

static int	unset_env(char **cmd, t_blst **envlst, int mode)
{
	int		i;
	t_blst	*target_node;

	i = 1;
	if (mode == IS_CHILD_PROCESS)
		return (OK);
	while (cmd[i] != NULL)
	{
		target_node = (t_blst *)doub_lstsearch(*envlst, cmd[i], cmp_key);
		if (target_node->u_data.env_data == NULL)
		{
			i ++;
			continue ;
		}
		target_node = doub_lstpurge((void *)&target_node);
		doub_lstdelone(target_node, free_env_data);
		i++;
	}
	return (OK);
}

static int	valid_option(char **cmd)
{
	if (!cmd[1])
	{
		unset_arg_err();
		return (GENERAL_ERR);
	}
	return (OK);
}
