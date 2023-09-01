/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:06:52 by rmarecar          #+#    #+#             */
/*   Updated: 2023/09/01 17:21:52 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_process(t_main *data)
{
	int	i;

	i = 0;
	if (data->hd_count)
	{
		while (i < data->hd_count)
		{
			close(data->here_doc[i].fd[0]);
			i++;
		}
		free(data->here_doc);
	}
	if (data->cmd_paths)
		free_tab(data->cmd_paths);
}

void	wait_exec(t_main *data)
{
	int	i;
	int	status;

	i = 0;
	signal(SIGINT, SIG_IGN);
	waitpid(data->pid_last, &status, 0);
	while (i < data->pipe_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	signal(SIGINT, sig_handler);
	if (WIFEXITED(status))
		data->return_value = WEXITSTATUS(status);
}

void	built_in_free(t_main *data)
{
	free_tab(data->cmd_paths);
	free_tab(data->env_bis);
	free_tab(data->env_exp);
	if (data->here_doc)
		free(data->here_doc);
	reset_stuff(data);
}
