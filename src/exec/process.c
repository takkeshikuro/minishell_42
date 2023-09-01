/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/09/01 19:31:48 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_ex(t_main *data, int fd[2], int old_fd[2], int *i)
{
	fd[0] = 0;
	fd[1] = 0;
	old_fd[0] = -1;
	old_fd[1] = -1;
	data->hd_pos = 0;
	*i = 0;
}

void	last_process(t_main *data, t_cmd_parse *node, char *cmd, int fd[2])
{
	last_redir(data, node, &fd[0], &fd[1]);
	if (fd[0] && node->hd_check == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	builtin_exec(data, node);
	cmd = get_command(data->cmd_paths, node->cmd_tab[0]);
	if (cmd == NULL)
		no_command(data, node);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd, node->cmd_tab, data->env_bis);
	free_tab(data->cmd_paths);
	free_tab(data->env_bis);
	free_tab(data->env_exp);
	reset_stuff(data);
	exit (1);
}
