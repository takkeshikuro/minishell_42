/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/07/07 00:13:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipe_init(t_main *data, t_cmd_parse *node)
{
	t_cmd_parse *tmp;

	tmp = node;
	data->path = find_path(data->env_bis);
	data->cmd_paths = ft_split(data->path, ':');
	data->hd_count = 0;
	data->here_doc = NULL;
	while (tmp)
	{
		if (tmp->redirection)
		{
			if (tmp->redirection->operateur == LEFT_LEFT)
				data->hd_count++;
		}
		tmp = tmp->next;
	}
	if (data->hd_count)
		data->here_doc = malloc(sizeof(t_here_doc) * data->hd_count);
}

void	no_command(t_main *data, t_cmd_parse *node)
{
	write(2, node->cmd_tab[0], ft_strlen(node->cmd_tab[0]));
	write(2, ": command not found\n", 20);
	exit(1);
}

void	pipe_work(t_main *data, int in, int out, t_cmd_parse *node, int hd_pos)
{
	pid_t	pid;
	char	*cmd;
	int		fd[2];
	int		hd;

	hd = 0;
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
			if (node->redirection->operateur == LEFT_LEFT)
			{
				dup2(data->here_doc[hd_pos].fd[0], 0);
				close(data->here_doc[hd_pos].fd[0]);
			}
			node->redirection = node->redirection->next;
		}
		if (in && !hd)
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

void	last_process(t_main *data, t_cmd_parse *node, char *cmd, int in, int hd_pos)
{
	int	out;
	int	pid;
	int	fd[2];
	int	hd;

	hd = 0;
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
		if (node->redirection->operateur == LEFT_LEFT)
		{
			hd = 1;
			dup2(data->here_doc[hd_pos].fd[0], 0);
			close(data->here_doc[hd_pos].fd[0]);
		}
		node->redirection = node->redirection->next;
	}
	if (in && hd == 0)
	{
		dup2(in, 0);
		close(in);
	}
	builtin_exec(data, node);
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
	int		hd_pos;

	hd_pos = 0;
	i = 0;
	in = 0;
	while (i < data->pipe_count)
	{
		pipe(fd);
		pipe_work(data, in, fd[1], node, hd_pos);
		close(fd[1]);
		in = fd[0];
		if (node->redirection)
		{
			if (node->redirection->operateur == LEFT_LEFT)
				hd_pos++;
		}
		node = node->next;
		i++;
	}
	if (data->pipe_count == 0 && contains_char(node->cmd_tab[0], '=') && node->cmd_tab[0][0] != '=')
	{
		add_v_to_envexp(data, node->cmd_tab[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
		last_process(data, node, cmd, in, 0); //test avec 0
}

void	execute_cmd(t_main *data)
{
	t_cmd_parse	*node;
	int			i;
	char		*cmd;
	int			len;
	int			pid;

	cmd = NULL;
	node = data->cmd_parse;
	len = ft_strlen(node->cmd_tab[0]);
	if (!ft_strncmp(node->cmd_tab[0], "exit", len))
		built_exit(data, node);
	data->pipe_count = lstsize(node) - 1;
	i = 0;
	pipe_init(data, node);
	while (i < data->hd_count)
	{
		pipe(data->here_doc[i].fd);
		pid = fork();
		if (pid == 0)
			here_doc_manage(data, node, data->here_doc[i].fd);
		waitpid(-1, NULL, 0);
		close(data->here_doc[i].fd[1]);
		i++;
	}
	i = 0;
	exec(data, node, cmd);
	while (i <= data->pipe_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}
