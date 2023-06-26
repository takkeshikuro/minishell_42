/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/06/26 20:16:01 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipe_init(t_main *data)
{
	data->path = find_path(data->env_bis);
	data->cmd_paths = ft_split(data->path, ':');
}

void	no_command(t_main *data, t_cmd_parse *node)
{
	write(2, node->cmd_tab[0], ft_strlen(node->cmd_tab[0]));
	write(2, ": command not found\n", 20);
	exit(1);
}

void	pipe_work(t_main *data, int in, int out, t_cmd_parse *node)
{
	pid_t	pid;
	char	*cmd;

	pid = fork();
	if (pid == 0)
	{
		while (node->redirection)
		{
			if (node->redirection->operateur == RIGHT)
				out = open_outfile(node);
			if (node->redirection->operateur == LEFT)
				in = open_infile(node);
			if (node->redirection->operateur == RIGHT_RIGHT)
				out = open_append(node);
			node->redirection = node->redirection->next;
		}
		if (in)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		cmd = get_command(data->cmd_paths, node->cmd_tab[0]);
		if (cmd == NULL)
			no_command(data, node);
		execve(cmd, node->cmd_tab, data->env_bis);
		exit(1);
	}
}

int	child_processes(t_main *data, t_cmd_parse *node)
{
	int	in;
	int	i;
	int	pid;
	int	out;
	int	fd[2];

	i = 0;
	in = 0;
	while (i < data->pipe_count)
	{
		pipe(fd);
		pipe_work(data, in, fd[1], node);
		close(fd[1]);
		in = fd[0];
		node = node->next;
		i++;
	}
	return (in);
}

void	last_process(t_main *data, t_cmd_parse *node, char *cmd, int in)
{
	int	out;

	while (node->redirection)
	{
		if (node->redirection->operateur == RIGHT)
		{
			out = open_outfile(node);
			dup2(out, 1);
			close(out);
		}
		if (node->redirection->operateur == LEFT)
			in = open_infile(node);
		if (node->redirection->operateur == RIGHT_RIGHT)
		{
			out = open_append(node);
			dup2(out, 1);
			close(out);
		}
		node->redirection = node->redirection->next;
	}
	if (in)
	{
		dup2(in, 0);
		close(in);
	}
	cmd = get_command(data->cmd_paths, node->cmd_tab[0]);
	if (cmd == NULL)
		no_command(data, node);	
	execve(cmd, node->cmd_tab, data->env_bis);
	exit (1);
}

void	exec(t_main *data, t_cmd_parse *node, char *cmd)
{
	int		i;
	int		in;
	int		pid;
	int		fd[2];

	i = 0;
	in = 0;
	while (i < data->pipe_count)
	{
		pipe(fd);
		pipe_work(data, in, fd[1], node);
		close(fd[1]);
		in = fd[0];
		node = node->next;
		i++;
	}
	pid = fork();
	if (pid == 0)
		last_process(data, node, cmd, in);
}

void	execute_cmd(t_main *data)
{
	t_cmd_parse	*node;
	int			i;
	char		*cmd;

	cmd = NULL;
	node = data->cmd_parse;
	data->pipe_count = lstsize(node) - 1;
	i = 0;
	pipe_init(data);
	exec(data, node, cmd);
	while (i <= data->pipe_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}
