/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:03:08 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/14 18:20:48 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_kill(t_main *data)
{
	free_tab(data->env_bis);
	if (data->cmd_parse->cmd_tab)
		free_tab(data->cmd_parse->cmd_tab);
	if (data->input_line[0])
		free(data->input_line);
}
