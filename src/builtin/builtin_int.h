/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:38:35 by saraki            #+#    #+#             */
/*   Updated: 2024/07/21 08:43:04 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_INT_H
# define BUILTIN_INT_H

# include "common.h"

// builtin_export.c
int		builtin_export(char **cmd, t_blst **envlst, int mode);
int		valid_format_key(char *cmd);
char	**get_key_val(char *cmd, int pos);
int		valid_identifier(char *cmd);

// builtin_export_print.c
int		export_print(t_blst *envlst, int mode);

// builtin_export_setenv.c
int		export_env(char **cmd, t_blst **envlst, int mode);

#endif