/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:07:45 by keshikuro         #+#    #+#             */
/*   Updated: 2023/06/25 01:29:15 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	show_env_exp(t_main *data)
{
	int i;

	i = 0;
	while (data->env_exp[i])
	{
		fprintf(stderr, "%s\n", data->env_exp[i]);
		i++;
	}
	data->return_value = 0;
	return (0);
}
