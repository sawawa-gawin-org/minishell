/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:29:37 by saraki            #+#    #+#             */
/*   Updated: 2024/05/07 16:34:52 by saraki           ###   ########.fr       */
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

// parser.c
int		parser(void **tokens_lst);
// expander.c
int		expander(void **tokens_lst, void **env_lst);

#endif