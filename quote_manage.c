/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 06:31:03 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/31 07:44:16 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	rm_quote(t_cmd_parse *node, int quote)
{
	

}

int	quote_manage(t_main *data)
{
	t_cmd_parse	*cmd_node;
	int			i;
	int			j;

	cmd_node = data->cmd_parse;
	while (cmd_node)
	{
		j = 0;
		while (cmd_node->cmd_tab[i])
		{
			if (cmd_node->cmd_tab[i][j] == 39)
				return (rm_qote(cmd_node, 39));		// simple quote
			else if (cmd_node->cmd_tab[i][j] == 34)
				return (rm_quote(cmd_node, 34)); // double quote
			j++;
		}
		i++;
	}
	cmd_node = cmd_node->next;
	return (0);
}
//in progress
