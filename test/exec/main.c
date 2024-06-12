/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:41:53 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/15 08:26:22 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include <unistd.h>

void	end(void)__attribute__((destructor));

void	end(void)
{
	system("leaks exec.out");
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
	
	char *cmd1[] = {"ls", "-la", ">", "a.txt", NULL};
	token_head_node = debug_parselst((char **)cmd1);
	if (token_head_node == NULL)
		return (1);
	exec((void *)token_head_node);
	doub_lstdelall((void **)&token_head_node, NULL);
	
	write(STDOUT_FILENO, "- - - - - -\n", 12);
	char *cmd2[] = {"ls", "-la", "|", "wc", "-l", NULL};
	token_head_node = debug_parselst((char **)cmd2);
	if (token_head_node == NULL)
		return (1);
	exec((void *)token_head_node);
	doub_lstdelall((void **)&token_head_node, NULL);
	
	write(STDOUT_FILENO, "- - - - - -\n", 12);
	char *cmd3[] = {"ls", "-la", "|", "wc", "-l", "|", "wc", "-l", NULL};
	token_head_node = debug_parselst((char **)cmd3);
	if (token_head_node == NULL)
		return (1);
	exec((void *)token_head_node);
	doub_lstdelall((void **)&token_head_node, NULL);

	write(STDOUT_FILENO, "- - - - - -\n", 12);
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
