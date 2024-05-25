/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:08:00 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/20 03:33:15 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "dbllst.h"
#include "libft.h"

// void	end(void)__attribute__((destructor));

// void	end(void)
// {
// 	system("leaks minishell");
// }

volatile sig_atomic_t	g_signal = 0;

static int	add_history_with_heredoc(char *line, char *heredoc_gained_str);
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
		heredoc_gained_str = parser(&tokens_lst, &env_lst);
		if (heredoc_gained_str == NULL)
			return (1); // err handling
		exec_tokenslst_cmds(tokens_lst); // err handling
		if (add_history_with_heredoc(line, heredoc_gained_str))
			return (1);
		doub_lstdelall(&tokens_lst, free_token_data);
	}
	doub_lstdelall(&env_lst, free_env_data);
	return (0);
}

static int	add_history_with_heredoc(char *line, char *heredoc_gained_str)
{
	char	*line_with_nl;
	char	*joined_str;

	if (heredoc_gained_str == NULL)
	{
		add_history(line);
		free(line);
		return (0);
	}
	line_with_nl = ft_strjoin(line, "\n");
	free(line);
	if (line_with_nl == NULL)
	{
		free(heredoc_gained_str);
		return (-1);
	}
	joined_str = ft_strjoin(line_with_nl, heredoc_gained_str);
	free(line_with_nl);
	free(heredoc_gained_str);
	if (line_with_nl == NULL)
		return (-1);
	add_history(joined_str);
	free(joined_str);
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
