/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/10 13:00:54 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

static void	put_tokens_lst(t_blst *tokens_lst);

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