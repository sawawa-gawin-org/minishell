/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/31 20:01:34 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

static void	put_tokens_lst(t_blst *tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;

	tmp = tokens_lst;
	while (tmp->data != NULL)
	{
		data = tmp->data;
		printf("text:%s, type:%d\n", data->token_str, data->token_type);
		tmp = tmp->next;
	}
}

static void	replace_noquote(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len - 2)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
}

static void	delete_quote(t_blst **tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;
	int				len;

	tmp = *tokens_lst;
	while (tmp->data != NULL)
	{
		len = 0;
		data = tmp->data;
		len = ft_strlen(data->token_str);
		if (len == 2)
		{
			if (DOUBLE_QUOTE_FLAG <= data->token_type && data->token_type <= SINGLE_QUOTE_FLAG)
				doub_lstpurge(&tmp);
		}
		else if (2 < len && data->token_str[0] == data->token_str[len - 1])
		{
			replace_noquote(data->token_str, len);
		}
		tmp = tmp->next;
	}
}

int	parser(t_blst **tokens_lst)
{
	printf("debug: parse start\n");
	if (!syntax_checker(*tokens_lst, cmp_syntax))
		return (0);
	delete_quote(tokens_lst);
	printf("debug: parse OK\n");
	put_tokens_lst(*tokens_lst);
	return (1);
}

//tokenリスト内を走査して、""空文字列要素を削除
//"hoge""huge$VAL"->hogehuge$VAL (blank(' ', '\t')を挟まずに)連続する文字列を結合
//クオートの削除
//<, >, <<, >> の後に来るtokenをdelimiter(デリミタ)やfileとする(token_typeの変更?)
//各リダイレクトを順に読み込み、最終的な入力や出力先を保持する。(ここでリダイレクトの処理をするか、exec部分で処理するかは未定)
//(リダイレクトリストを作成？)
//ヒアドキュメントの展開
//変数展開 ARG="ho hoge"; ec$ARG がありえる
//"|"区切りでコマンド列ごとに分割
//< infile | echo hoge のような、実行可能コマンドがない場合も考慮して実装する。