/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/09/02 23:55:02 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_dup2close(int fd[2], int check)
{
	if (!check)
	{
		if (fd[1] != 1)
		{
			if (fd[0] > -1)
				close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		return ;
	}
	else
	{
		if (fd[0] != -1)
			close(fd[0]);
		return ;
	}
}

void	pipe_work(t_main *data, int fd[2], t_cmd_parse *node, int old_fd[2])
{
	pid_t	pid;
	char	*cmd;

	pid = fork();
	cmd = NULL;
	if (pid == 0)
	{
		close_hds(data, node);
		if (redir_pipe(data, node, &old_fd[0], &fd[1]) == -2)
			exit_error_redir(data, fd);
		if (old_fd[0] != -1 && node->hd_check == 0)
		{
			dup2(old_fd[0], 0);
			close(old_fd[0]);
		}
		ft_dup2close(fd, 0);
		builtin_exec(data, node);
		cmd = get_command(data, data->cmd_paths, node->cmd_tab[0]);
		if (cmd == NULL)
			ft_dup2close(old_fd, 1);
		if (cmd == NULL)
			close(fd[0]);
		ft_execve(data, node, cmd);
	}
	ft_dup2close(old_fd, 1);
}

void	exec2(t_main *data, t_cmd_parse *node, char *cmd, int fd[2])
{
	data->pid_last = fork();
	if (data->pid_last == 0)
		last_process(data, node, cmd, fd);
	if (data->pipe_count)
	{
		close(fd[1]);
		close(fd[0]);
	}
}

void	exec(t_main *data, t_cmd_parse *node, char *cmd)
{
	int		i;
	int		fd[2];
	int		old_fd[2];

	init_ex(data, fd, old_fd, &i);
	while (i < data->pipe_count)
	{
		pipe(fd);
		node->hd_check = 0;
		pipe_work(data, fd, node, old_fd);
		if (old_fd[0] != -1)
			close(old_fd[0]);
		if (node->hdc)
			data->hd_pos++;
		old_fd[0] = fd[0];
		old_fd[1] = fd[1];
		close(fd[1]);
		node = node->next;
		i++;
	}
	exec2(data, node, cmd, fd);
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
	if (here_doc_init(data, node, 0) == 42)
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
