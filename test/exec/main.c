/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:41:53 by syamasaw          #+#    #+#             */
/*   Updated: 2024/07/01 06:44:09 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "common.h"

#include <unistd.h>

// void	end(void)__attribute__((destructor));

// void	end(void)
// {
// 	system("leaks exec.out");
// }

static t_blst *debug_parselst(char **cmd);

int	main(int argc, char **argv, char **envp)
{
	t_blst	*token_head_node;
	int		status;
	
	// char *cmd1[] = {"ls", "-la", NULL};
	// token_head_node = debug_parselst((char **)cmd1);
	// if (token_head_node == NULL)
	// 	return (1);
	// exec((void *)token_head_node);
	// doub_lstdelall((void **)&token_head_node, NULL);
	
	// write(STDOUT_FILENO, "- - - - - -\n", 12);
	// char *cmd2[] = {"cat", "<", "subject.md", NULL};
	// token_head_node = debug_parselst((char **)cmd2);
	// if (token_head_node == NULL)
	// 	return (1);
	// exec((void *)token_head_node);
	// doub_lstdelall((void **)&token_head_node, NULL);
	
	// write(STDOUT_FILENO, "- - - - - -\n", 12);
	// char *cmd3[] = {"cat", "<", "subject.md", "|", "wc", "-l", NULL};
	// token_head_node = debug_parselst((char **)cmd3);
	// if (token_head_node == NULL)
	// 	return (1);
	// exec((void *)token_head_node);
	// doub_lstdelall((void **)&token_head_node, NULL);

	write(STDOUT_FILENO, "- - - - - -\n", 12);
	char *cmd4[] = {"asdfasdf", NULL};
	token_head_node = debug_parselst((char **)cmd4);
	if (token_head_node == NULL)
		return (1);
	status = exec((void *)token_head_node, envp);
	printf("status: %d\n", status); // exit status 127
	doub_lstdelall((void **)&token_head_node, NULL);

	write(STDOUT_FILENO, "- - - - - -\n", 12);
	char *cmd5[] = {"/dev/null", NULL};
	token_head_node = debug_parselst((char **)cmd5);
	if (token_head_node == NULL)
		return (1);
	status = exec((void *)token_head_node, envp);
	printf("status: %d\n", status); // exit status 126
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
