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

static int	is_blank_str(char *str);
void		sig_handler(int signal);

int	minishell(int argc, char *argv[], char *envp[])
{
	struct termios	term; //端末の属性を変更する用の構造体
	struct termios	save; //変更前の属性を保存する用の構造体
	char			*line; //readlineで読み取った文字列用のchar*
	t_token			*tokens; //字句分割後のトークン格納用の双方向連結リスト
	t_shval			*shvals; //環境変数およびシェル変数用の双方向連結リスト
	t_blst			*shvals_lst; //組み込みコマンドのリスト

	(void)argc;
	(void)argv;
	shvals = NULL;
	shvals = get_env_all(envp, shvals); //既存の環境変数のリスト化
	shvals_lst = new_get_env_all(envp);
	doub_lstdelall(&shvals_lst, free_shval_data);
	// put_lst_shval(shvals);
	tcgetattr(STDIN_FILENO, &save); //初期状態の取得
	term = save; //複製
	term.c_lflag &= ~(ECHOCTL); //制御文字を消す
	tcsetattr(STDIN_FILENO, TCSANOW, &term); //変更を即時反映
	signal(SIGQUIT, SIG_IGN); //SIGQUIT(Ctrl+\)を無視
	signal(SIGINT, sig_handler); //SIGINT(Ctrl+C)をハンドリング sigaction SA_RESTART
	line = NULL;
	while (1)
	{
		tokens = NULL;
		line = readline("minishell$ "); //Ctrl+Dを押してEOFするとreadlineがNULLを返す。
		if (line == NULL)
			break ;
		if (line[0] != '\0') //もし空白やタブなどの入力が行われている場合は履歴に残す。改行だけなら残さない。cmdの成否にかかわらず履歴に残る。
			add_history(line);
		if (is_blank_str(line)) //lineがisspace()の文字のみであればcontinue
		{
			free(line);
			continue ;
		}
		tokens = tokenizer(line, tokens);
		if (parser(&tokens))
			put_lst(tokens);
		del_lst(tokens);
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &save);
	del_lst_shval(shvals);
	return (0);
}

static int	is_blank_str(char *str)
{
	int	i;

	i = 0;
	while (is_blank(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	is_blank(int c)
{
	return (c == ' ' || c == '\t');
}

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
