/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-18 03:02:38 by syamasaw          #+#    #+#             */
/*   Updated: 2024-09-18 03:02:38 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "tokens.h"
#include "dbllst.h"
#include "libft.h"

static int	main_loop(void *env_lst, int flag);
static char	*wrapper_readline(int flag);
static int	execute(char *line, void *env_lst, void **tokens_lst);
static int	handle_blank(char *line, void *env_lst);

int	read_eval_print_loop(void *env_lst, int flag)
{
	int	status;

	while (CONTINUE)
	{
		init_signal(handler_for_outer_readline, SIG_IGN);
		init_rl_for_prompt();
		status = main_loop(env_lst, flag);
		if (status == ERR || status == EXIT_CALLED || flag == 0)
			break ;
		else if (status == CONTINUE)
			continue ;
	}
	return (status);
}

static int	main_loop(void *env_lst, int flag)
{
	char	*line;
	void	*tokens_lst;
	int		status;
	int		result;

	g_signal = 0;
	line = wrapper_readline(flag);
	result = handle_blank(line, env_lst);
	if (result != OK)
		return (result);
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

static char	*wrapper_readline(int flag)
{
	char	*line;
	int		old_stderr;
	int		dev_null;

	if (!flag)
	{
		old_stderr = dup(STDERR_FILENO);
		dev_null = open("/dev/null", O_WRONLY);
		dup2(dev_null, STDERR_FILENO);
		close(dev_null);
	}
	line = readline(SHELL_PROMPT);
	if (!flag)
	{
		dup2(old_stderr, STDERR_FILENO);
		close(old_stderr);
	}
	return (line);
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

static int	handle_blank(char *line, void *env_lst)
{
	int	i;

	if (line == NULL)
		return (ERR);
	i = 0;
	while (is_blank(line[i]))
		i++;
	if (line[i] != '\0')
		return (OK);
	free(line);
	if (g_signal != 0)
		if (add_exit_status_as_env(&env_lst, g_signal + 128))
			return (ERR);
	return (CONTINUE);
}
