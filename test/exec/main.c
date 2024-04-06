/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:41:53 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/06 04:29:08 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exec.h"
#include "dbllst.h"

#include <unistd.h>

void	end(void)__attribute__((destructor));

void	end(void)
{
	system("leaks pipex.out");
}

typedef struct s_node
{
	struct s_node	*prev;
	char			*data;
	struct s_node	*next;
}				t_blst;

static t_blst *debug_parselst(char **cmd);

int	main(void)
{
	t_blst	*token_head_node;
	
	char *cmd1[] = {"ls", "-la", NULL};
	token_head_node = debug_parselst((char **)cmd1);
	if (token_head_node == NULL)
		return (1);
	exec((void *)token_head_node);
	doub_lstdelall((void **)&token_head_node, NULL);
	
	write(STDOUT_FILENO, "- - - - - -\n", 13);
	char *cmd2[] = {"ls", "-la", "|", "wc", "-l", NULL};
	token_head_node = debug_parselst((char **)cmd2);
	if (token_head_node == NULL)
		return (1);
	exec((void *)token_head_node);
	doub_lstdelall((void **)&token_head_node, NULL);
	
	write(STDOUT_FILENO, "- - - - - -\n", 13);
	char *cmd3[] = {"ls", "-la", "|", "wc", "-l", "|", "wc", "-l", NULL};
	token_head_node = debug_parselst((char **)cmd3);
	if (token_head_node == NULL)
		return (1);
	exec((void *)token_head_node);
	doub_lstdelall((void **)&token_head_node, NULL);

	write(STDOUT_FILENO, "- - - - - -\n", 13);
	char *cmd4[] = {"ls", "-la", "|", "wc", "-l", "|", "wc", "-l", "|", "wc", "-l", NULL};
	token_head_node = debug_parselst((char **)cmd4);
	if (token_head_node == NULL)
		return (1);
	exec((void *)token_head_node);
	doub_lstdelall((void **)&token_head_node, NULL);
	return (0);
}

static t_blst *debug_parselst(char **cmd)
{
	t_blst	*head_node;
	t_blst	*new_node;
	int i = 0;

	head_node = doub_lstnew(NULL);
	while (head_node != NULL && cmd[i] != NULL)
	{
		new_node = doub_lstnew(cmd[i]);
		if (new_node == NULL)
		{
			doub_lstdelall((void **)&head_node, NULL);
			return (NULL);
		}
		doub_lstappend((void **)&head_node, new_node);
		i++;
	}
	return (head_node);
}

// #include <sys/types.h>
// #include <sys/wait.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>

// int
// main(int argc, char *argv[])
// {
// 	int pipefd[2];
// 	pid_t cpid;
// 	char buf;

// 	if (argc != 2) {
// 		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pipe(pipefd) == -1) {
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}

// 	cpid = fork();
// 	if (cpid == -1) {
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (cpid == 0) {    /* Child reads from pipe */
// 		close(pipefd[1]);          /* Close unused write end */

// 		while (read(pipefd[0], &buf, 1) > 0)
// 			write(STDOUT_FILENO, &buf, 1);

// 		write(STDOUT_FILENO, "\n", 1);
// 		close(pipefd[0]);
// 		_exit(EXIT_SUCCESS);

// 	} else {            /* Parent writes argv[1] to pipe */
// 		close(pipefd[0]);          /* Close unused read end */
// 		write(pipefd[1], argv[1], strlen(argv[1]));
// 		close(pipefd[1]);          /* Reader will see EOF */
// 		wait(NULL);                /* Wait for child */
// 		exit(EXIT_SUCCESS);
// 	}
// }
