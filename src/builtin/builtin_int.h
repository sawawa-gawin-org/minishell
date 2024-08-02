/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:38:35 by saraki            #+#    #+#             */
/*   Updated: 2024/08/02 21:37:02 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_INT_H
# define BUILTIN_INT_H

# include "common.h"

# define PATHNAME_SIZE 1023

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