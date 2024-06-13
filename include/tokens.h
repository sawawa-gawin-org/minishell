/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:29:37 by saraki            #+#    #+#             */
/*   Updated: 2024/06/13 17:13:12 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

// init_env.c
void	*init_env(void);
void	free_env_data(void *data);

// tokenizer.c
void	*tokenizer(char **line);
int		is_blank(int c);
void	free_token_data(void *data);

int		exec_tokenslst_cmds(void *tokens_lst);

// syntax_checker.c
int		syntax_checker(void *lst, void *cmp_f);
int		cmp_syntax(void *d, void *n);

// parser.c
int		parser(void **tokens_lst, void **env_lst);

// expander.c
int		expander(void **tokens_lst, void **env_lst);

// error_print.c
int		error_println(char *str);

#endif