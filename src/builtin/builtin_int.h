/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:38:35 by saraki            #+#    #+#             */
/*   Updated: 2024/09/14 14:59:39 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_INT_H
# define BUILTIN_INT_H

# include "common.h"

# define PATHNAME_SIZE 1023

typedef struct s_cd_path_routing
{
	char		*src;
	char		*dist;
}				t_cd_path_routing;

enum			e_CD_MODE
{
	NO_OPTION = 0,
	GO_HOME = 1,
	L_FLAG = 1 << 1,
	P_FLAG = 1 << 2,
	E_FLAG = 1 << 3,
	AT_FLAG = 1 << 4,
	GO_OLDPWD = 1 << 5,
};

// core.c
int		update_or_create_env(char *key, char *value, t_blst **envlst);

// builtin_cd.c
int		builtin_cd(char **cmd, t_blst **envlst, int mode);

// builtin_cd_utils.c
char	*allocate_cwd_path(t_blst *envlst);
int		get_home_path(char **path, t_blst *envlst);
int		get_oldpwd_path(char **path, t_blst *envlst);
int		cd_check_err(char *path, t_cd_path_routing *routing);

// builtin_echo.c
int		builtin_echo(char **cmd, t_blst **envlst, int mode);

// builtin_env.c
int		builtin_env(char **cmd, t_blst **envlst, int mode);

// builtin_export.c
int		builtin_export(char **cmd, t_blst **envlst, int mode);
// builtin_export_utils.c
int		export_print(t_blst *envlst, int mode);
int		export_env(char **cmd, t_blst **envlst, int mode);

// builtin_pwd.c
int		builtin_pwd(char **cmd, t_blst **envlst, int mode);

// builtin_exit.c
int		builtin_exit(char **cmd, t_blst **envlst, int mode);
// builtin_exit_utils.c
int		parse_str_to_numeric(char *argv, size_t *value);

// builtin_unset.c
int		builtin_unset(char **cmd, t_blst **envlst, int mode);

#endif