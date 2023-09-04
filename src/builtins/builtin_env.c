/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 08:01:06 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/15 14:37:28 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_env(t_main *data, t_cmd_parse *cmd_parse)
{
	int	i;

	i = 0;
	(void)cmd_parse;
	while (data->env_bis[i])
	{
		ft_putendl_fd(data->env_bis[i], 1);
		i++;
	}
	data->return_value = 0;
	return (0);
}
