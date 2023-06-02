/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 06:31:03 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/02 22:30:30 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	rm_quote(t_cmd_parse *node, int i_tab, int quote)
{
	int	j;
	int i;

	j = 0;
	i = 0;
	char *new;
	
	if (node->cmd_tab[i_tab][0] == quote)
		node->cmd_tab[i_tab] = ft_strim(node->cmd_tab[i_tab], quote);
	else
	{
		new = malloc(sizeof(char) * ft_strlen(node->cmd_tab[i_tab]));
		if (!new)
			exit (1);
		while (node->cmd_tab[i_tab][j])
		{
			if (node->cmd_tab[i_tab][j] == quote)
				j++;
			new[i] = node->cmd_tab[i_tab][j];
			i++;
			j++;
		}
		new[i] == '\0';
		node->cmd_tab[i_tab] = ft_strdup(new);
	}
	
	if (quote == 39)
		return (0);
	else
		return (1);
}

int	quote_manage(t_main *data)
{
	t_cmd_parse	*cmd_node;
	int			i;
	int			j;

	
	cmd_node = data->cmd_parse;
	while (cmd_node)
	{
		i = 0;
		while (cmd_node->cmd_tab[i] != NULL)
		{
			j = 0;
			
			while (cmd_node->cmd_tab[i][j])
			{
				if (cmd_node->cmd_tab[i][j] == 39)
					return (rm_quote(cmd_node, i, 39));		// simple quote
				else if (cmd_node->cmd_tab[i][j] == 34)
					return (rm_quote(cmd_node, i, 34)); // double quote
				j++;
			}
			i++;
		}
		cmd_node = cmd_node->next;
		if (!cmd_node)
			return (0);
	}
	return (0);
}
