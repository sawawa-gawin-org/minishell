/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:41:53 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/05 05:12:54 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	end(void)__attribute__((destructor));

void	end(void)
{
	system("leaks pipex.out");
}

int	main(int argc, char *argv[], char *envp[])
{
	// pipex(argc, argv, envp);
	char *str;
	
	str = join_args_with_space(argc, argv);
	write(1,str,1);
	(void) envp;
	return (0);
}

// int	main(int argc, char *argv[])
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
