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

	in = open(node->redirection->str, O_RDWR);
	if (in == -1)
	{
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
	exit (127);
}
