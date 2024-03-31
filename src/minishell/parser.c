/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/31 16:52:26 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

int	parser(t_blst **tokens_lst)
{
	printf("debug: parse start\n");
	if (!syntax_checker(*tokens_lst, cmp_syntax))
		return (0);
	printf("debug: parse OK\n");
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