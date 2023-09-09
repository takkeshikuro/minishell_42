/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:40 by keshikuro         #+#    #+#             */
/*   Updated: 2023/09/02 22:43:13 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exit_arg_manage(char **cmd_tab, int i)
{
	while (cmd_tab[1][i])
	{	
		if (ft_isalpha(cmd_tab[1][i]) || (cmd_tab[1][i] == '+' && i != 0))
		{
			ft_putendl_fd("exit", 1);
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(cmd_tab[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (2);
		}
		i++;
	}
	i = 0;
	while (cmd_tab[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("bash: exit: too many arguments", 2);
		return (0);
	}
	ft_putendl_fd("exit", 1);
	return (ft_atoi(cmd_tab[1]));
}

int	built_exit(t_main *data, t_cmd_parse *cmd_parse)
{
	int	ok;

	ok = 0;
	while (cmd_parse->cmd_tab[ok])
		ok++;
	if (ok == 1)
	{
		ft_putendl_fd("exit", 1);
		data->return_value = 0;
	}
	else
	{
		ok = exit_arg_manage(cmd_parse->cmd_tab, 0);
		if (ok == 0)
		{
			data->return_value = 127;
			return (1);
		}
		else
			data->return_value = ok;
	}
	reset_stuff(data);
	free_kill(data);
	exit (data->return_value);
}
