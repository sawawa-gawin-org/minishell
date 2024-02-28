/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:08:00 by syamasaw          #+#    #+#             */
/*   Updated: 2024/02/28 14:23:06 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(char *line)
{
	int	i;

	i = 4;
	if (line[4] == ' ')
	{
		while (line[i] == ' ')
			i++;
		printf("%s", line + 5);
	}
	printf("\n");
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

int	main(int argc, char *argv[], char *envp[])
{
	struct termios	term; //端末の属性を変更する用の構造体
	struct termios	save; //変更前の属性を保存する用の構造体
	char			*line; //readlineで読み取った文字列用のchar*

	tcgetattr(STDIN_FILENO, &save); //初期状態の取得
	term = save; //複製
	term.c_lflag &= ~(ECHOCTL); //制御文字を消す
	tcsetattr(STDIN_FILENO, TCSANOW, &term); //変更を即時反映
	signal(SIGQUIT, SIG_IGN); //SIGQUIT(Ctrl+\)を無視
	signal(SIGINT, sig_handler); //SIGINT(Ctrl+C)をハンドリング
	line = NULL;
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		else if (strlen(line) == 0)
		{
			free(line);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			continue ;
		}
		else if (strncmp(line, "exit", 4) == 0)
		{
			printf("exit\n");
			free(line);
			break ;
		}
		else if (strncmp(line, "echo", 4) == 0)
			ft_echo(line);
		add_history(line);
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &save);
	return (0);
}
