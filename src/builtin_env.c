/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 08:01:06 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/25 08:12:43 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	built_env(t_main *data, t_cmd_parse *cmd_parse)
{
	int	i;

	i = 0;
	(void)cmd_parse;
	while (data->env_ok[i])
	{
		printf("%s\n", data->env_ok[i]);
		i++;
	}
	return (0);
}
