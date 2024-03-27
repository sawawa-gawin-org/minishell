/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:08:00 by syamasaw          #+#    #+#             */
/*   Updated: 2024/02/29 15:52:24 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "dbllst.h"

int	minishell(char *envp[])
{
	struct termios		term; //端末の属性を変更する用の構造体
	struct termios		save; //変更前の属性を保存する用の構造体
	t_shval				*shvals; //環境変数およびシェル変数用の双方向連結リスト
	struct sigaction	sa;

	shvals = NULL;
	shvals = get_env_all(envp, shvals); //既存の環境変数のリスト化
	tcgetattr(STDIN_FILENO, &save); //初期状態の取得
	term = save; //複製
	term.c_lflag &= ~(ECHOCTL); //制御文字を消す
	tcsetattr(STDIN_FILENO, TCSANOW, &term); //変更を即時反映
	set_signal(SIGINT, sig_handler, &sa);
	set_signal(SIGQUIT, SIG_IGN, &sa);
	//シェル初期化処理ここまで
	repl(shvals, &sa);//loop
	tcsetattr(STDIN_FILENO, TCSANOW, &save);
	del_lst_shval(shvals);
	return (0);
}
