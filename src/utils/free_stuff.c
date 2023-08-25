/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:03:08 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/25 03:40:46 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	free_cmd_tab(t_main *data)
{
	t_cmd_parse	*tmp;

	tmp = data->cmd_parse;
	while (tmp)
	{
		free_tab(tmp->cmd_tab);
		tmp->cmd_tab = NULL;
		tmp = tmp->next;
	}
}

void	free_cmd_lst(t_cmd_parse *lst)
{
	t_cmd_parse	*tmp;

	tmp = lst;
	while (tmp)
	{
		lst = tmp->next;
		if (tmp)
			free(tmp);
		tmp = lst;
	}
	free(lst);
}

void	free_lxr_lst(t_lexer *lst)
{
	t_lexer	*tmp;
	t_lexer	*next;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		if (!tmp->next)
		{
			free(tmp->str);
			free(tmp);
			return ;
		}
		next = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = next;
	}
}
