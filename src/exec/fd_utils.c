/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/09/01 20:37:32 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_hds(t_main *data, t_cmd_parse *node)
{
	int	i;

	i = 0;
	if (node->hdc == 0)
	{
		while (i < data->hd_count)
		{
			if (data->here_doc[i].fd[0] > -1)
				close(data->here_doc[i].fd[0]);
			i++;
		}
		return ;
	}
	while (i < data->hd_count)
	{
		if (i != data->hd_pos)
		{
			if (data->here_doc[i].fd[0] > -1)
				close(data->here_doc[i].fd[0]);
		}
		i++;
	}
}

int	open_outfile(t_main *data, t_cmd_parse *node, int old_fd)
{
	int	out;

	if (old_fd > 1)
		close(old_fd);
	out = open(node->redirection->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (out == -1)
	{
		perror(node->redirection->str);
		free_tab(data->cmd_paths);
		free_tab(data->env_bis);
		free_tab(data->env_exp);
		return (-2);
	}
	return (out);
}

int	open_infile(t_main *data, t_cmd_parse *node, int old_fd)
{
	int	in;

	node->hd_check = 0;
	in = open(node->redirection->str, O_RDWR);
	if (in == -1)
	{
		if (old_fd > -1)
			close(old_fd);
		perror(node->redirection->str);
		free_tab(data->cmd_paths);
		free_tab(data->env_bis);
		free_tab(data->env_exp);
		return (-2);
	}
	return (in);
}

int	open_append(t_main *data, t_cmd_parse *node, int old_fd)
{
	int	out;

	if (old_fd > 1)
		close(old_fd);
	out = open(node->redirection->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (out == -1)
	{
		perror(node->redirection->str);
		free_tab(data->cmd_paths);
		free_tab(data->env_bis);
		free_tab(data->env_exp);
		return (-2);
	}
	return (out);
}

void	exit_access(t_main *data, char *cmd)
{
	perror(cmd);
	free_process(data);
	reset_stuff(data);
	free_kill(data);
	exit (126);
}
