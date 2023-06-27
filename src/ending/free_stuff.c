/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:03:08 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/27 03:30:46 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tab(char **tab)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (tab[i])
		i++;
	while (i <= j)
		free(tab[i++]);
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
