/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:38:35 by saraki            #+#    #+#             */
/*   Updated: 2024/08/04 11:45:46 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_INT_H
# define BUILTIN_INT_H

# include "common.h"

# define PATHNAME_SIZE 1023

// builtin_cd.c
int		builtin_cd(char **cmd, t_blst **envlst, int mode);
char	*allocate_cwd_path(t_blst *envlst);
char	*create_abspath(char *relpath, t_blst **envlst);
int		update_pwd_and_oldpwd_env(
			char *old_pwd, char *new_pwd, t_blst **envlst);

// builtin_echo.c
int		builtin_echo(char **cmd, t_blst **envlst, int mode);

// builtin_env.c
int		builtin_env(char **cmd, t_blst **envlst, int mode);

// builtin_export.c
int		builtin_export(char **cmd, t_blst **envlst, int mode);
int		valid_format_key(char *cmd);
char	**get_key_val(char *cmd, int pos);
int		valid_identifier(char *cmd);

// builtin_export_print.c
int		export_print(t_blst *envlst, int mode);

// builtin_export_setenv.c
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