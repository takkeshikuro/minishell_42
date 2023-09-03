/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:15:22 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/30 03:04:20 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	option_check(char *s)
{
	int	i;

	i = 0;
	if (s[i++] != '-')
		return (1);
	while (s[i])
	{
		if (s[i] != 'n')
			return (1);
		i++;
		if (s[i] == '\0')
			return (0);
	}
	return (0);
}

void	echo_print(char **tab, int ok)
{
	int	i;

	i = 1;
	while (tab[i])
	{
		if (!ok)
		{
			while (!option_check(tab[i]))
				i++;
		}
		ft_putstr_fd(tab[i], 1);
		i++;
		if (tab[i])
			ft_putchar_fd(32, 1);
	}
	if (ok)
		ft_putendl_fd(NULL, 1);
	return ;
}

int	built_echo(t_main *data, t_cmd_parse *cmd_parse)
{
	int	i;

	i = 1;
	if (cmd_parse->cmd_tab[1])
	{
		if (!ft_strncmp(cmd_parse->cmd_tab[1], "-n", 2))
		{
			while (cmd_parse->cmd_tab[1][i] == 'n')
				i++;
			if (cmd_parse->cmd_tab[1][i] == '\0')
				echo_print(cmd_parse->cmd_tab, 0);
			else
				echo_print(cmd_parse->cmd_tab, 1);
		}
		else
			echo_print(cmd_parse->cmd_tab, 1);
	}
	else if (!cmd_parse->cmd_tab[1])
		ft_putendl_fd(NULL, 1);
	data->return_value = 0;
	return (0);
}
