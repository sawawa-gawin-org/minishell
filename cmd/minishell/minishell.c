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
static int	main_loop(void *env_lst);
static int	execute(char *line, void *env_lst, void **tokens_lst);
static int	is_blank_str(char *str);

int	main(int argc, char **argv, char **envp)
{
	void	*env_lst;
	int		status;

	(void)argc;
	(void)argv;
	env_lst = init_envlst(envp);
	if (env_lst == NULL)
		return (1);
	while (CONTINUE)
	{
		init_signal(handler_for_outer_readline, SIG_IGN);
		init_rl_for_prompt();
		status = main_loop(env_lst);
		if (status == ERR)
			break ;
		else if (status == EXIT_CALLED)
			break ;
		else if (status == CONTINUE)
			continue ;
	}
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

static int	main_loop(void *env_lst)
{
	char	*line;
	void	*tokens_lst;
	int		status;

	line = readline("minishell$ ");
	if (g_signal != 0)
		g_signal = 0;
	if (line == NULL)
		return (ERR);
	if (is_blank_str(line))
	{
		free(line);
		return (CONTINUE);
	}
	tokens_lst = tokenizer(&line);
	if (tokens_lst == NULL)
	{
		free(line);
		return (ERR);
	}
	status = execute(line, env_lst, &tokens_lst);
	free(line);
	doub_lstdelall(&tokens_lst, free_token_data);
	return (status);
}

static int	execute(char *line, void *env_lst, void **tokens_lst)
{
	int	exit_status;

	add_history(line);
	if (!syntax_checker(*tokens_lst, cmp_syntax))
	{
		if (add_exit_status_as_env(&env_lst, 2))
			return (ERR);
		return (CONTINUE);
	}
	exit_status = parser(tokens_lst, &env_lst);
	if (exit_status == ERR)
		return (ERR);
	if (g_signal == 0 && exit_status == OK)
	{
		if (exec_tokenslst_cmds(*tokens_lst, &env_lst, &exit_status))
			return (ERR);
		if (exit_status == EXIT_CALLED)
			return (EXIT_CALLED);
	}
	else if (g_signal != 0)
		exit_status = g_signal + 128;
	g_signal = 0;
	if (add_exit_status_as_env(&env_lst, exit_status))
		return (ERR);
	return (OK);
}

static int	is_blank_str(char *str)
{
	int	i;

	i = 0;
	while (is_blank(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
