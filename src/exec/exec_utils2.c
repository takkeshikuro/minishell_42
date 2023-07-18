/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:57:05 by rmarecar          #+#    #+#             */
/*   Updated: 2023/07/18 20:01:29 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	no_command(t_main *data, t_cmd_parse *node)
{
	write(2, node->cmd_tab[0], ft_strlen(node->cmd_tab[0]));
	write(2, ": command not found\n", 20);
	exit(127);
}

void	pipe_init(t_main *data, t_cmd_parse *node)
{
	t_cmd_parse	*tmp;

	tmp = node;
	data->path = find_path(data->env_bis);
	data->cmd_paths = ft_split(data->path, ':');
	data->hd_count = 0;
	data->here_doc = NULL;
	while (tmp)
	{
		if (tmp->redirection)
		{
			if (tmp->redirection->operateur == LEFT_LEFT)
				data->hd_count++;
		}
		tmp = tmp->next;
	}
	if (data->hd_count)
		data->here_doc = malloc(sizeof(t_here_doc) * data->hd_count);
}
