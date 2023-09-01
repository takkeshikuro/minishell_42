/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/09/01 17:20:44 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipe_work(t_main *data, int fd[2], t_cmd_parse *node, int old_fd[2])
{
	pid_t	pid;
	char	*cmd;

	pid = fork();
	node->hd_check = 0;
	cmd = NULL;
	if (pid == 0)
	{
		redir_pipe(data, node, &old_fd[0], &fd[1]);
		if (old_fd[0] != -1 && node->hd_check == 0)
		{
			dup2(old_fd[0], 0);
			close(old_fd[0]);
		}
		if (fd[1] != 1)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		builtin_exec(data, node);
		cmd = get_command(data->cmd_paths, node->cmd_tab[0]);
		if (cmd == NULL)
		{
			if (old_fd[0] != -1)
				close(old_fd[0]);
			close(fd[0]);
		}
		ft_execve(data, node, cmd);
	}
	if (old_fd[0] != -1)
		close(old_fd[0]);
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

void	exec(t_main *data, t_cmd_parse *node, char *cmd)
{
	int		i;
	int		fd[2];
	int		old_fd[2];
	
	fd[0] = 0;
	fd[1] = 0;
	old_fd[0] = -1;
	old_fd[1] = -1;
	data->hd_pos = 0;
	i = 0;
	while (i < data->pipe_count)
	{
		pipe(fd);
		pipe_work(data, fd, node, old_fd);
		if (old_fd[0] != -1)
			close(old_fd[0]);
		if (node->redirection)
		{
			if (node->redirection->operateur == LEFT_LEFT)
				data->hd_pos++;
		}
		old_fd[0] = fd[0];
		old_fd[1] = fd[1];
		close(fd[1]);
		node = node->next;
		i++;
	}
	data->pid_last = fork();
	if (data->pid_last == 0)
		last_process(data, node, cmd, fd);
	if (data->pipe_count)
	{
		close(fd[1]);
		close(fd[0]);
	}
}

void	execute_cmd(t_main *data)
{
	t_cmd_parse	*node;
	char		*cmd;

	cmd = NULL;
	node = data->cmd_parse;
	data->pipe_count = lstsize(node) - 1;
	if (first_builtins(data, node))
		return ;
	pipe_init(data, node);
	if (here_doc_init(data, node) == 42)
	{
		free_tab(data->cmd_paths);
		free(data->here_doc);
		data->return_value = 130;
		return ;
	}
	exec(data, node, cmd);
	wait_exec(data);
	free_process(data);
}
