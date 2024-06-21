/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:26:55 by saraki            #+#    #+#             */
/*   Updated: 2024/06/21 05:44:57 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_INT_H
# define ENV_INT_H

# define OK 0
# define ERR -1
# define IS_EXPORTED 1
# define NOT_EXPORTED 0

typedef struct s_env_data
{
	char	*key;
	char	*val;
	int		exported;
}			t_env_data;

typedef struct s_node
{
	struct s_node	*prev;
	t_env_data		*e_data;
	struct s_node	*next;
}			t_blst;

// init_env.c
t_blst		*new_env_node(char *str, int flag);
t_env_data	*new_env_data(char *str, int flag);
void		free_env_data(void *data);

// add_shell_env.c
int			add_exit_status_as_env(void **env_lst, int status);
int			add_shell_env(char *key, char *val, void **env_lst);
char		*join_keyval(char *key, char *val);

char		**convert_envlst_to_arr(void *env_lst);


#endif