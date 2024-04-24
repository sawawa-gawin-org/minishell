/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:08:00 by syamasaw          #+#    #+#             */
/*   Updated: 2024/02/29 15:52:24 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "dbllst.h"

static int	is_blank_str(char *str);

volatile sig_atomic_t	g_signal = 0;

int	minishell(char *envp[])
{
	char			*line;
	t_blst			*tokens_lst;
	t_blst			*shvals_lst;

	shvals_lst = get_env_all(envp);
	if (shvals_lst == NULL)
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
		parser(&tokens_lst);
		// if (parser(&tokens_lst))
		// {
		// 	// expand
		// 	exec_tokenslst_cmds(tokens_lst);
		// }
		// exec_tokenslst_cmds(tokens_lst);
		free(line);
		doub_lstdelall((void **)&tokens_lst, free_token_data);
	}
	doub_lstdelall((void **)&shvals_lst, free_shval_data);
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
