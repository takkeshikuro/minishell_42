/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:03:08 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/09/03 04:07:02 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tab(char **tab)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!tab)
		return ;
	while (tab[j])
		j++;
	if (j == i)
	{
		free(tab);
		return ;
	}
	while (i <= j)
		free(tab[i++]);
	free(tab);
}

void	free_kill(t_main *data)
{
	free_tab(data->env_bis);
	data->env_bis = NULL;
	free_tab(data->env_exp);
	data->env_exp = NULL;
	free_tab(data->hidetab);
	data->hidetab = NULL;
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
		{
			free_lxr_lst(tmp->redirection);
			free(tmp);
		}
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
