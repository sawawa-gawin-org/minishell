/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:31:30 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/27 15:39:36 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "dbllst.h"
# include "libft.h"
# include "minishell.h"

// parser.c
int		parser(t_blst **tokens_lst);
// syntax_checker.c
int		syntax_checker(t_blst *lst, t_cmp_f cmp_f);
int		cmp_syntax(void *d, void *n);
// delete_quote.c
void	delete_quote(t_blst **tokens_lst);
// merge_redirects.c
void	merge_redirects(t_blst **tokens_lst);
// delete_blank.c
void	delete_blank(t_blst **tokens_lst);

#endif