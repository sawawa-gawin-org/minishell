/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:35:20 by syamasaw          #+#    #+#             */
/*   Updated: 2024/06/26 15:58:19 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

// static void	put_tokens_lst(t_blst *tokens_lst);

/* 
# Expansion
-> confirm `man bash` ("EXPANSION")

Quote Removal
	After the preceding expansions, all unquoted occurrences of the
	characters \, ', and "  that did not result from one of the above
	expansions are removed.
*/

int	expander(t_blst **tokens_lst, t_blst **env_lst)
{
	if (!expand_env(tokens_lst, *env_lst))
		return (0);
	return (1);
}
