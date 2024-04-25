/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:35:20 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/25 18:00:36 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "dbllst.h"

static void	put_tokens_lst(t_blst *tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;
	int				i;

	tmp = tokens_lst;
	i = 1;
	while (tmp->data != NULL)
	{
		data = tmp->data;
		printf("%d: text:%s, type:%d, sub:%d\n", i, data->token_str, data->token_type, data->sub_type);
		tmp = tmp->next;
		i++;
	}
}

static void	expand_val(t_blst **tokens_lst, t_blst *env_lst) //ボツ
{
	t_blst			*tmp;
	t_env_data		*envdata;
	t_token_data	*tokendata;

	tmp = env_lst;
	envdata = tmp->data;
	tokendata = (*tokens_lst)->data;
	while (tmp->data != NULL)
	{
		envdata = tmp->data;
		if (ft_strcmp(tokendata->token_str + 1, envdata->key) == 0)
		{
			overwrite();
			return ;
		}
		tmp = tmp->next;
	}
	// envになければ削除
}

int	expander(t_blst **tokens_lst, t_blst **env_lst)
{
	// 変数の展開
	
	put_tokens_lst(*tokens_lst);
	return (1);
}

//1. tokenlstから変数を含むtokenを見つける
//2. tokenstrから$を見つける
//3. $以降、$か空白か終端までの文字列を変数リストから探す
//4. あったらそれに置き換え、なければ$文字列を削除
//5. 2に戻り、token_strが終端まで探し終わったらbreak

//printfと同じじゃね...?
