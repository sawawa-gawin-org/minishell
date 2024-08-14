/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:29:37 by saraki            #+#    #+#             */
/*   Updated: 2024/08/14 13:44:57 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

// tokenizer.c
void	*tokenizer(char **line);
int		is_blank(int c);
void	free_token_data(void *data);

int		exec_tokenslst_cmds(void *tokens_lst, void *env_lst, int *status);

// syntax_checker.c
int		syntax_checker(void *lst, void *cmp_f);
int		cmp_syntax(void *d, void *n);

// parser.c
int		parser(void **tokens_lst, void **env_lst);

// expander.c
int		expander(void **tokens_lst, void *env_lst);

#endif