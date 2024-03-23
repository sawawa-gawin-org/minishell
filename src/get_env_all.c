/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:37:15 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/23 18:32:03 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	strlen_eq(char *str);

t_shval	*get_env_all(char **envp, t_shval *shvals)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		shvals = lstadd_shval(shvals, envp[i], strlen_eq(envp[i]), 1);
	}
	return (shvals);
}

static int	strlen_eq(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}
