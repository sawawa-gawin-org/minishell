/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:41:27 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/19 18:29:45 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

static void	lstdel_middle_n(t_blst **lst, int n);
static int	rewrite_token(t_blst **lst, char *str, int type);

//tokens_lstを読み込み、ヒアドキュメント記号<<を見つける。
int	heredoc_put(t_blst **tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;
	int				i;
	char			*heredoc_str;

	tmp = *tokens_lst;
	while (tmp->data != NULL)
	{
		data = tmp->data;
		if (data->token_type == HEREDOC_FLAG) //ヒアドキュメントの記号<<を見つけたら
		{
			//data->token_typeがSPACE_FLAG以外になるまでtokens_lstを読み込む
			tmp = tmp->next;
			data = tmp->data;
			i = 1; //<<(0)空白(1)EOF(2)
			while (data->token_type == SPACE_FLAG) //SPACE_FLAG以外になるまでtokens_lstを読み込む
			{
				tmp = tmp->next;
				data = tmp->data;
				i++; //デリミタの位置を記録
			}
			heredoc_str = heredoc_open(data->token_str);
			if (!heredoc_str)
				return (0);
			tmp = tmp->next;
			lstdel_middle_n(&tmp, i);
			rewrite_token(&tmp, heredoc_str, DOUBLE_QUOTE_VAL_FLAG);
			free(heredoc_str);
		}
		else
			tmp = tmp->next;
	}
	return (1);
}

static void	lstdel_middle_n(t_blst **lst, int n)
{
	t_blst	*tmp;
	t_blst	*purged;

	tmp = *lst;
	while (n > 0)
	{
		purged = doub_lstpurge((void **)&tmp->prev);
		doub_lstdelone(purged, free_token_data);
		n--;
	}
}

static int	rewrite_token(t_blst **lst, char *str, int type)
{
	t_token_data	*data;

	data = (*lst)->prev->data;
	if (data->token_str)
		free(data->token_str);
	data->token_str = ft_strdup(str);
	if (!data->token_str)
		return (0);
	data->token_type = type;
	return (1);
}
