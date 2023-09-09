/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:57:05 by rmarecar          #+#    #+#             */
/*   Updated: 2023/09/03 00:42:29 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	no_command(t_main *data, t_cmd_parse *node)
{
	int	i;

	i = 0;
	if (!node->redirection)
		print_no_command(data, node->cmd_tab[0], 0);
	free_tab(data->cmd_paths);
	free_tab(data->env_bis);
	free_tab(data->env_exp);
	free_tab(data->hidetab);
	reset_stuff(data);
	while (i < data->hd_count)
	{
		if (data->here_doc[i].fd[0] > -1)
			close(data->here_doc[i].fd[0]);
		if (data->here_doc[i].fd[0] > -1)
			close(data->here_doc[i].fd[1]);
		i++;
	}
	if (data->here_doc)
		free(data->here_doc);
	exit(127);
}

void	hdc_init(t_main *data)
{
	int	i;

	i = 0;
	if (data->hd_count)
	{
		data->here_doc = malloc(sizeof(t_here_doc) * data->hd_count);
		if (!data->here_doc)
			error_mallc(data);
		while (i < data->hd_count)
		{
			data->here_doc[i].pos = 0;
			i++;
		}
	}
}

void	first_pinit(t_main *data)
{
	data->cmd_paths = NULL;
	data->path = find_path(data->env_bis);
	data->cmd_paths = ft_split(data->path, ':');
	data->hd_count = 0;
	data->here_doc = NULL;
}

void	pipe_init(t_main *data, t_cmd_parse *node)
{
	t_cmd_parse	*tmp;
	t_lexer		*tmpr;

	first_pinit(data);
	tmp = node;
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
	free_tab(data->cmd_paths);
	free_tab(data->env_bis);
	free_tab(data->env_exp);
	reset_stuff(data);
	exit(1);
}
