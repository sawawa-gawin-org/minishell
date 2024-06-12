/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:08:00 by syamasaw          #+#    #+#             */
/*   Updated: 2024/06/12 13:35:26 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "dbllst.h"

// void	end(void)__attribute__((destructor));

// void	end(void)
// {
// 	system("leaks minishell");
// }

volatile sig_atomic_t	g_signal = 0;

static int	main_loop(void *env_lst);
static int	execute(char *line, void *env_lst, void *tokens_lst);
static int	is_blank_str(char *str);

int	main(void)
{
	void	*env_lst;
	int		status;

	env_lst = init_env();
	if (env_lst == NULL)
		return (1);
	init_signal();
	while (CONTINUE)
	{
		status = main_loop(env_lst);
		if (status == ERR)
			break ;
		else if (status == CONTINUE)
			continue ;
	}
	doub_lstdelall(&env_lst, free_env_data);
	return (OK);
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
	status = execute(line, env_lst, tokens_lst);
	free(line);
	doub_lstdelall(&tokens_lst, free_token_data);
	return (status);
}

static int	execute(char *line, void *env_lst, void *tokens_lst)
{
	char	*heredoc_gained;
	int		err;

	heredoc_gained = NULL;
	if (!syntax_checker(tokens_lst, cmp_syntax))
		return (CONTINUE);
	if (parser(&tokens_lst, &env_lst, &heredoc_gained))
		return (ERR);
	if (exec_tokenslst_cmds(tokens_lst))
	{
		free(heredoc_gained);
		return (ERR);
	}
	err = add_history_wraper(line, heredoc_gained);
	free(heredoc_gained);
	if (err)
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
