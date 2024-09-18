/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:08:00 by syamasaw          #+#    #+#             */
/*   Updated: 2024/09/14 19:12:16 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "tokens.h"
#include "dbllst.h"
#include "libft.h"

// void	end(void)__attribute__((destructor));

// void	end(void)
// {
// 	system("leaks minishell");
// }

volatile sig_atomic_t	g_signal = 0;

static void	*init_envlst(char **envp);

int	main(int argc, char **argv, char **envp)
{
	void	*env_lst;
	int		status;
	int		flag;

	(void)argc;
	(void)argv;
	flag = isatty(STDIN_FILENO);
	env_lst = init_envlst(envp);
	if (env_lst == NULL)
		return (1);
	status = read_eval_print_loop(env_lst, flag);
	if (status == ERR && errno == 0)
		ft_putstr_fd("\nexit\n", 2);
	doub_lstdelall(&env_lst, free_env_data);
	return (OK);
}

static void	*init_envlst(char **envp)
{
	void	*env_lst;

	env_lst = create_envlist(envp);
	if (env_lst == NULL)
		return (NULL);
	if (update_shlvl(&env_lst))
	{
		doub_lstdelall(&env_lst, free_env_data);
		return (NULL);
	}
	return (env_lst);
}
