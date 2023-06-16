/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 06:31:03 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/16 16:37:05 by keshikuro        ###   ########.fr       */
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

int	quote_manage(t_main *data, t_cmd_parse *node, int i)
{
	int			j;

	j = 0;
	while (node->cmd_tab[i][j])
	{
		if (node->cmd_tab[i][j] == 39)
			return (rm_quote(node, i, 39)); // simple quote
		else if (node->cmd_tab[i][j] == 34)
			return (rm_quote(node, i, 34)); // double quote
		j++;
	}
	return (0);
}
