/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:57:05 by rmarecar          #+#    #+#             */
/*   Updated: 2023/08/31 12:35:24 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	no_command(t_main *data, t_cmd_parse *node)
{
	int	i;

	i = 0;
	if (node->cmd_tab[0])
	{
		write(2, node->cmd_tab[0], ft_strlen(node->cmd_tab[0]));
		write(2, ": command not found\n", 20);
	}
	free_tab(data->cmd_paths);
	free_tab(data->env_bis);
	free_tab(data->env_exp);
	reset_stuff(data);
	while (i < data->hd_count)
	{
		close(data->here_doc[i].fd[0]);
		close(data->here_doc[i].fd[1]);
		i++;
	}
	exit(127);
}

void	hdc_init(t_main *data)
{
	int	i;

	i = 0;
	if (data->hd_count)
	{
		data->here_doc = malloc(sizeof(t_here_doc) * data->hd_count);
		while (i < data->hd_count)
		{
			data->here_doc[i].pos = 0;
			i++;
		}
	}
}

void	pipe_init(t_main *data, t_cmd_parse *node)
{
	t_cmd_parse	*tmp;
	t_lexer		*tmpr;
	
	data->cmd_paths = NULL;
	tmp = node;
	data->path = find_path(data->env_bis);
	data->cmd_paths = ft_split(data->path, ':');
	data->hd_count = 0;
	data->here_doc = NULL;
	while (tmp)
	{
		tmp->hdc = 0;
		if (tmp->redirection)
		{
			tmpr = tmp->redirection;
			while (tmpr)
			{
				if (tmpr->operateur == LEFT_LEFT)
					tmp->hdc++;
				tmpr = tmpr->next;
			}
			if (tmp->hdc)
				data->hd_count++;
		}
		tmp = tmp->next;
	}
	hdc_init(data);
}

void	ft_execve(t_main *data, t_cmd_parse *node, char *cmd)
{
	if (cmd == NULL)
		no_command(data, node);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd, node->cmd_tab, data->env_bis);
	exit(1);
}
