/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 06:31:03 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/13 00:43:04 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*need_malloc(t_cmd_parse *node, int i)
{
	int		size;
	char	*str;

	size = ft_strlen(node->cmd_tab[i]);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		exit (1);
	return (str);
}

int	rm_quote(t_cmd_parse *node, int i_tab, int quote)
{
	char	*new;
	int		j;
	int		i;

	j = 0;
	i = 0;
	if (node->cmd_tab[i_tab][0] == quote)
		node->cmd_tab[i_tab] = ft_strim(node->cmd_tab[i_tab], quote);
	else
	{
		new = need_malloc(node, i_tab);
		while (node->cmd_tab[i_tab][j])
		{
			if (node->cmd_tab[i_tab][j] == quote)
				j++;
			new[i] = node->cmd_tab[i_tab][j];
			i++;
			j++;
		}
		new[i] = '\0';
		node->cmd_tab[i_tab] = ft_strdup(new);
	}
	if (quote == 39)
		return (1);
	return (0);
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
					return (rm_quote(cmd_node, i, 39)); // simple quote
				else if (cmd_node->cmd_tab[i][j] == 34)
					return (rm_quote(cmd_node, i, 34)); // double quote
				j++;
			}
			i++;
		}
		cmd_node = cmd_node->next;
	}
	return (0);
}
