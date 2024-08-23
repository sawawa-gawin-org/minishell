/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-23 09:07:46 by syamasaw          #+#    #+#             */
/*   Updated: 2024-08-23 09:07:46 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static int	check_ambigious_redir(t_blst *tokens_lst);
static int	is_redir_without_heredoc(int flag);

int	expand_and_check_ambiguous(t_blst **tokens_lst, t_blst *env_lst)
{
	t_token_data	*data;
	char			*tmp;

	data = (*tokens_lst)->u_data.token_data;
	tmp = ft_strdup(data->token_str);
	if (tmp == NULL)
		return (ERR);
	if (!expand_env_as_str(data, env_lst))
		return (ERR);
	if (ft_strcmp(data->token_str, "") == 0)
	{
		if (check_ambigious_redir((*tokens_lst)->prev) != OK)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(tmp, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
		}
	}
	free(tmp);
	return (OK);
}

static int	check_ambigious_redir(t_blst *tokens_lst)
{
	t_token_data	*data;

	while (tokens_lst->u_data.token_data != NULL)
	{
		data = tokens_lst->u_data.token_data;
		if (data->token_type & SPACE_FLAG)
			tokens_lst = tokens_lst->prev;
		else if (is_redir_without_heredoc(data->token_type))
			return (ERR);
		else
			break ;
	}
	return (OK);
}

static int	is_redir_without_heredoc(int flag)
{
	if (flag & (LESS_FLAG | GREAT_FLAG | APPEND_FLAG))
		return (1);
	return (0);
}
