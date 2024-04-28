/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:41:20 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/27 18:44:12 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "dbllst.h"
# include "libft.h"
# include "minishell.h"

// expander.c
int		expander(t_blst **tokens_lst, t_blst **env_lst);
// expand_env.c
int		expand_env(t_blst **tokens_lst, t_blst *env_lst);
// expand_util.c
char	*add_val_to_str(char *tokstr, char *str, int *now_old, t_blst *envlst);
int		get_val_len(char *str, int now);
char	*strjoin_allfree(char *str1, char *str2);

#endif