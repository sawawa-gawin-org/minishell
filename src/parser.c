/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/13 16:01:15 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
Parser
1. read token list.
2. checks for syntax inconsistencies (e.g. ls > | echo, ls -l | | cat)
3. if inconsistencies are found, the flow comes to a halt and an error is returned.
*/

//変数の展開、空文字列""の削除、クオートの削除、文字列同士の結合

int	syntax_checker(t_token *tokens)
{
	while (tokens != NULL)
	{
		if (tokens->prev == NULL && tokens->token_type == 1)
			return (0);//先頭が|
		if (tokens->next != NULL)
		{
			if (tokens->token_type == 1 && tokens->next->token_type == 1)
				return (0);//| |
			if (less <= tokens->token_type && tokens->token_type <= append)
			{
				if (tokens->next->token_type == tube)
					return (0);//redirect |
				if (less <= tokens->next->token_type && tokens->next->token_type <= append)
					return (0);//redirect redirect
			}
		}
		else
			if (tube <= tokens->token_type && tokens->token_type <= append)
				return (0);//redirect EOF or | EOF
		if (tokens->token_type == open_quote)
			return (0);
		tokens = tokens->next;
	}
	return (1);
}
