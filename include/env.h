/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:27:17 by saraki            #+#    #+#             */
/*   Updated: 2024/07/21 07:23:09 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
// create_envlist.c
void	*create_envlist(char **env);
void	free_env_data(void *data);

// convert_envlst.c
char	**convert_envlst_to_arr(void *env_lst);
void	free_environment_array(char **env);

// add_shell_env.c
int		add_exit_status_as_env(void **env_lst, int status);
int		add_shell_env(char *key, char *val, void **env_lst);

//print_env.c
void	print_env(void *env_lst);

// sort_env.c
void	qsort_env(char **env, int low, int high);

#endif