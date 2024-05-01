/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:08:00 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/01 16:11:36 by saraki           ###   ########.fr       */
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

static int	is_blank_str(char *str);

volatile sig_atomic_t	g_signal = 0;

int	minishell(void)
{
	char			*line;
	void			*tokens_lst;
	void			*env_lst;

	env_lst = init_env();
	if (env_lst == NULL)
		return (1);
	init_signal();
	line = NULL;
	while (1)
	{
		tokens_lst = NULL;
		line = readline("minishell$ ");
		if (g_signal != 0)
			g_signal = 0;
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		if (is_blank_str(line))
		{
			free(line);
			continue ;
		}
		tokens_lst = new_tokenizer(&line);
		if (parser(&tokens_lst))
		{
			if (!expander(&tokens_lst, &env_lst))
				exit(1);
			exec_tokenslst_cmds(tokens_lst);
		}
		// exec_tokenslst_cmds(tokens_lst);
		free(line);
		doub_lstdelall(&tokens_lst, free_token_data);
	}
	doub_lstdelall(&env_lst, free_env_data);
	return (0);
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

int	is_blank(int c)
{
	return (c == ' ' || c == '\t');
}
