/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:03:08 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/07/19 16:24:14 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
t_cmd_parse	*clear_one(t_cmd_parse *lst)
{
	if (lst->cmd_tab[0])
		free_tab(lst->cmd_tab);
	free(lst);
}

void	free_cmd_list(t_main *data)
{
	t_cmd_parse	*tmp;
	t_cmd_parse	*start;
	int			i;

	tmp = data->cmd_parse;
	start = tmp;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	tmp = start;
	while (i < 0)
	{
		clear_one(tmp);
		i--;
	}
}*/

void	free_tab(char **tab)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (tab[j])
		j++;
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
