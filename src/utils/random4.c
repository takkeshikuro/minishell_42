/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 04:33:52 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/09/07 07:50:10 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	empty_case(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (!tab[i][0])
			return (1);
	}
	return (0);
}

int	check_qt_tab(t_cmd_parse *node, int i, int j)
{
	if (!node->cmd_tab[i][0])
		return (0);
	while (node->cmd_tab[i])
	{
		j = 0;
		if (ft_strlen(node->cmd_tab[i]))
		{
			while (node->cmd_tab[i][j])
			{
				if (node->cmd_tab[i][j] == ' ')
				{
					if (node->cmd_tab[i][j] != '\0')
						return (1);
					while (node->cmd_tab[i][j] == ' ')
						j++;
					if (node->cmd_tab[i][j] != '\0')
						return (1);
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}
