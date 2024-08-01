/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:34:17 by saraki            #+#    #+#             */
/*   Updated: 2024/08/01 15:29:05 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "dbllst.h"
#include "env.h"

static int	valid_option(char **cmd);
static int	print_pwd(t_blst *envlst);
static int	get_cwd_from_cmd(void);

/**
 * Retrieves the current working directory and prints it to the standard
 * output.
 *
 * @param cmd The command and its arguments.
 * @param envlst The list of environment variables.
 * @param mode The execution mode.
 * @return Returns 0 on success, -1 on failure.
 */
int	builtin_pwd(char **cmd, t_blst **envlst, int mode)
{
	int		status;

	if (mode == IS_MAIN_PROCESS)
		return (OK);
	status = valid_option(cmd);
	if (status > 0)
		return (status);
	status = print_pwd(*envlst);
	if (status > 0)
		return (status);
	return (OK);
}

static int	print_pwd(t_blst *envlst)
{
	t_blst	*target_node;
	char	*key;

	key = "PWD";
	target_node = (t_blst *)doub_lstsearch(envlst, key, cmp_key);
	if (target_node->u_data.env_data == NULL)
		return (get_cwd_from_cmd());
	printf("%s\n", target_node->u_data.env_data->val);
	return (OK);
}

static int	get_cwd_from_cmd(void)
{
	char	pathname[PATHNAME_SIZE];

	if (getcwd(pathname, PATHNAME_SIZE) == NULL)
		return (GENERAL_ERR); // this status code should be set later
	printf("%s\n", pathname);
	return (OK);
}

static int	valid_option(char **cmd)
{
	if (cmd[1] != NULL)
	{
		pwd_err(cmd[1]);
		return (MISUSE_OF_SHELL_BUILTINS);
	}
	return (OK);
}
