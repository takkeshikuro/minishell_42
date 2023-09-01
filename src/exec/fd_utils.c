/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/09/01 17:13:25 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_outfile(t_main *data, t_cmd_parse *node, int old_fd)
{
	int	out;

	if (old_fd != -1 && old_fd)
		close(old_fd);
	out = open(node->redirection->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (out == -1)
	{
		perror(node->redirection->str);
		free_tab(data->cmd_paths);
		free_tab(data->env_bis);
		free_tab(data->env_exp);
		reset_stuff(data);
		exit(1);
	}
	return (out);
}

int	open_infile(t_main *data, t_cmd_parse *node, int old_fd)
{
	int	in;

	if (old_fd != -1 && old_fd)
		close(old_fd);
	in = open(node->redirection->str, O_RDWR);
	if (in == -1)
	{
		perror(node->redirection->str);
		free_tab(data->cmd_paths);
		free_tab(data->env_bis);
		free_tab(data->env_exp);
		reset_stuff(data);
		exit(1);
	}
	return (in);
}

int	open_append(t_main *data, t_cmd_parse *node, int old_fd)
{
	int	out;

	if (old_fd != -1 && old_fd)
		close(old_fd);
	out = open(node->redirection->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (out == -1)
	{
		perror(node->redirection->str);
		free_tab(data->cmd_paths);
		free_tab(data->env_bis);
		free_tab(data->env_exp);
		reset_stuff(data);
		exit(1);
	}
	return (out);
}
