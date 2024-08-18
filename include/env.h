/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:27:17 by saraki            #+#    #+#             */
/*   Updated: 2024/08/17 17:21:31 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
// create_envlist.c
void	*create_envlist(char **env);
void	free_env_data(void *data);

// convert_envlst.c
char	**create_env_arr_from_lst(void *env_lst, int is_val_is_nullable);
void	free_environment_array(char **env);

// add_shell_env.c
int		add_exit_status_as_env(void **env_lst, int status);
int		add_shell_env(char *key, char *val, void **env_lst);
char	*strjoin_with_sep(char *str1, char *str2, char sep);
int		cmp_key(void *data, void *query_pt);

//print_env.c
void	print_env(void *env_lst);

// sort_env.c
void	qsort_env(char **env, int low, int high);

// update_shlvl.c
int		update_shlvl(void **envlst);

#endif