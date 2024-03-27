/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:26:30 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/27 13:45:29 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dbllst.h"

static int	is_blank_str(char *str);

int	new_repl(t_blst *shvals, struct sigaction *sa)
{
	t_blst	*tokens;
	char	*line;

	(void)shvals;
	line = NULL;
	while (1)
	{
		tokens = NULL;
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		if (is_blank_str(line))
		{
			free(line);
			continue ;
		}
		// tokens = tokenizer(line, tokens);
		tokens = new_tokenizer(line);
		if (parser(&tokens, sa))
			put_lst(tokens);
		del_lst(tokens);
		free(line);
	}
	return (0);
}

int	repl(t_shval *shvals, struct sigaction *sa)
{
	t_token	*tokens;
	char	*line;

	(void)shvals;
	line = NULL;
	while (1)
	{
		tokens = NULL;
		line = readline("minishell$ "); //Ctrl+Dを押してEOFするとreadlineがNULLを返す。
		if (!line)
			break ;
		if (line[0] != '\0') //もし空白やタブなどの入力が行われている場合は履歴に残す。改行だけなら残さない。cmdの成否にかかわらず履歴に残る。
			add_history(line);
		if (is_blank_str(line)) //lineが' 'または'\t'であればcontinue
		{
			free(line);
			continue ;
		}
		tokens = tokenizer(line, tokens);
		if (parser(&tokens, sa))
			put_lst(tokens);
		del_lst(tokens);
		free(line);
	}
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
