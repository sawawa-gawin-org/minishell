/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:13:18 by saraki            #+#    #+#             */
/*   Updated: 2024/08/04 11:48:25 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "env.h"
#include "dbllst.h"
#include "libft.h"

static int	valid_option(char **cmd, char path);

int	builtin_cd(char **cmd, t_blst **envlst, int mode)
{
	int		status;
	char	*path;
	char	*formed_path;
	char	*old_pwd;
	char	*pwd;

	path = NULL;
	if (mode == IS_CHILD_PROCESS)
		return (OK);
	status = valid_option(cmd, &path);
	if (status > 0)
		return (status);
	if (!is_abspath(path))
		formed_path = create_abspath(path, *envlst);
	if (formed_path == NULL)
		return (GENERAL_ERR);
	old_pwd = allocate_cwd_path(*envlst);
	if (old_pwd == NULL)
	{
		free(formed_path);
		return (GENERAL_ERR);
	}
	if (chdir(formed_path) == -1)
	{
		free(formed_path);
		return (GENERAL_ERR);
	}
	pwd = allocate_cwd_path(*envlst);
	free(formed_path);
	if (pwd == NULL)
	{
		free(old_pwd);
		return (GENERAL_ERR);
	}
	if (update_pwd_and_oldpwd_env(old_pwd, pwd, envlst) != OK)
		return (GENERAL_ERR);
	return (OK);
}

static int is_abspath(char *path)
{
	if (path[0] == '/')
		return (1);
	return (0);
}

static int	valid_option(char **cmd, char path)
{
	if (cmd[1] != NULL)
	{
		env_argc_err();
		return (MISUSE_OF_SHELL_BUILTINS);
	}
	if (cmd[1][0] == '-')
	{
		if (ft_strcmp(cmd[1], "-L") == 0)
			return (OK);
	}
	return (OK);
}
