/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:29:37 by saraki            #+#    #+#             */
/*   Updated: 2024/08/02 19:41:31 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_INT_H
# define TOKENS_INT_H

# include "libft.h"
# include "dbllst.h"
# include "common.h"

# include <stdio.h>
# include <stddef.h>
# include <fcntl.h>
# include <sys/wait.h> // Linux
# include <sys/stat.h> // Linux

# include <errno.h>

# include <readline/readline.h>
# include <readline/history.h>

extern volatile sig_atomic_t	g_signal;

// tokenizer.c
void		free_token_data(void *data);
int			is_blank(int c);
// tokenizer_util.c
char		*allocate_next_token(char **line, int *next_token_type);
int			is_val(char *str);

/* parser */
// syntax_checker.c
int			syntax_checker(t_blst *lst, t_cmp_f cmp_f);
// heredoc.c
int			parse_heredoc(t_blst **tokens_lst);
void		update_token_str_data(
				t_token_data *target_data, char *new_token_str);
int			is_flag(char *heredoc_str, int type);
// heredoc_utils.c
int			set_heredoc_string_to_node(
				char *delimiter, t_token_data *target_node);

int			cmp_syntax(void *d, void *n);
// delete_quote.c
void		delete_quote(t_blst **tokens_lst);
// delete_blank.c
void		delete_blank(t_blst **tokens_lst);
void		purge_token_node(t_blst **lst);

/* expander */
// expander.c
int			expander(t_blst **tokens_lst, t_blst **env_lst);
// expand_env.c
int			expand_env(t_blst **tokens_lst, t_blst *env_lst);
// expand_util.c
char		*add_val_to_str(
				char *tokstr, char *str, t_indexes *index, t_blst *envlst);
int			get_val_len(char *str, int now);
char		*strjoin_allfree(char *str1, char *str2);


#endif