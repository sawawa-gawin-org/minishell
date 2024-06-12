/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:08:00 by syamasaw          #+#    #+#             */
/*   Updated: 2024/06/12 12:15:30 by saraki           ###   ########.fr       */
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

static int	is_blank_str(char *str);

int	main(void)
{
	char			*line;
	void			*tokens_lst;
	void			*env_lst;
	char			*heredoc_gained_str;

	env_lst = init_env();
	if (env_lst == NULL)
		return (1);
	init_signal();
	line = NULL;
	heredoc_gained_str = NULL;
	while (1)
	{
		tokens_lst = NULL;
		line = readline("minishell$ ");
		if (g_signal != 0)
			g_signal = 0;
		if (line == NULL)
			break ;
		if (is_blank_str(line))
		{
			free(line);
			continue ;
		}
		tokens_lst = tokenizer(&line); // NULL check
		if (parser(&tokens_lst, &env_lst, &heredoc_gained_str))
			return (1); // err handling
		exec_tokenslst_cmds(tokens_lst); // err handling
		if (add_history_wraper(line, heredoc_gained_str))
			return (1);
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
