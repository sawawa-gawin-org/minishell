/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:29:38 by saraki            #+#    #+#             */
/*   Updated: 2024/05/07 20:17:50 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_TEST_H
# define TOKENS_TEST_H

# include "tokens.h"
# include "dbllst.h"

# include <stdio.h>
# include <stdlib.h>

typedef struct s_node
{
	struct s_node	*prev;
	char			*data;
	struct s_node	*next;
}				t_blst;

t_blst *commandStringToList(char *cmd);
void	dealocateList(t_blst **lst);

#endif