/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-16 09:50:51 by syamasaw          #+#    #+#             */
/*   Updated: 2024-08-16 09:50:51 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"
#include "dbllst.h"

static int	analyze_current_shlvl(char *shlvl_val);
static int	set_shlvl(int shlvl);

int	update_shlvl(void **envlst)
{
	t_blst	*shlvl_node;
	int		shlvl;
	char	*new;

	shlvl_node = (t_blst *)doub_lstsearch(*envlst, "SHLVL", cmp_key);
	if (shlvl_node->u_data.env_data != NULL)
	{
		shlvl = analyze_current_shlvl(shlvl_node->u_data.env_data->val);
		shlvl = set_shlvl(shlvl);
		free(shlvl_node->u_data.env_data->val);
		new = ft_itoa(shlvl + 1);
		if (new == NULL)
			return (ERR);
		shlvl_node->u_data.env_data->val = ft_strdup(new);
		free(new);
		return (OK);
	}
	return (add_shell_env("SHLVL", "1", envlst));
}

static int	analyze_current_shlvl(char *shlvl_val)
{
	int		i;
	int		shlvl;

	if (shlvl_val == NULL || shlvl_val[0] == '\0')
		return (0);
	i = -1;
	while (shlvl_val[++i] != '\0')
	{
		if (!ft_isdigit(shlvl_val[i]))
		{
			if (i == 0 && (shlvl_val[i] == '-' || shlvl_val[i] == '+'))
				continue ;
			return (0);
		}
	}
	shlvl = ft_atoi(shlvl_val);
	return (shlvl);
}

static int	set_shlvl(int shlvl)
{
	if (shlvl < 0)
		return (-1);
	else if (shlvl + 1 >= SHLVL_MAX)
	{
		ft_putstr_fd(MSG_PREFIX, 2);
		ft_putstr_fd("warning: shell level (", 2);
		ft_putnbr_fd(shlvl + 1, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		return (SHLVL_MIN);
	}
	return (shlvl);
}
