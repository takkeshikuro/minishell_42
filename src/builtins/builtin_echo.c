/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:15:22 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/28 08:38:56 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	echo_print(char **tab, int ok)
{
	int	check_option;

	if (ok == 1)
		check_option = 1;
	else
		check_option = 0;
	while (tab[ok])
	{
		ft_putstr_fd(tab[ok], 1);
		ok++;
		if (tab[ok])
			ft_putchar_fd(32, 1);
	}
	if (check_option)
		ft_putendl_fd(NULL, 1);
}

int	built_echo(t_main *data, t_cmd_parse *cmd_parse)
{
	int	i;

	i = 1;
	if (!ft_strncmp(cmd_parse->cmd_tab[1], "-n", 2))
	{
		while (cmd_parse->cmd_tab[1][i] == 'n')
			i++;
		if (cmd_parse->cmd_tab[1][i] == '\0')
			echo_print(cmd_parse->cmd_tab, 2);
		else
			echo_print(cmd_parse->cmd_tab, 1);
		return (0);
	}
	echo_print(cmd_parse->cmd_tab, 1);
	data->return_value = 0;
	return (0);
}
