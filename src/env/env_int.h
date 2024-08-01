/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:26:55 by saraki            #+#    #+#             */
/*   Updated: 2024/08/01 15:22:57 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_INT_H
# define ENV_INT_H

# define IS_EXPORTED 1
# define NOT_EXPORTED 0

# include "common.h"
# include "libft.h"

// create_envlist.c
t_env_data	*new_env_data(char *str, int flag);
void		free_env_data(void *data);

// add_shell_env.c
int			add_exit_status_as_env(void **env_lst, int status);
int			add_shell_env(char *key, char *val, void **env_lst);
char		*join_keyval(char *key, char *val);
int			cmp_key(void *data, void *query_pt);

// convert_envlst.c
char		**convert_envlst_to_arr(t_blst *env_lst);
void		free_environment_array(char **env);

#endif
