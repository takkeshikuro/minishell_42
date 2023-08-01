/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/08/01 21:16:01 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipe_work(t_main *data, int in, int out, t_cmd_parse *node)
{
	pid_t	pid;
	char	*cmd;
	int		fd[2];

	pid = fork();
	node->hd_check = 0;
	cmd = NULL;
	if (pid == 0)
	{
		redir_pipe(data, node, &in, &out);
		if (in && node->hd_check == 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		builtin_exec(data, node);
		cmd = get_command(data->cmd_paths, node->cmd_tab[0]);
		ft_execve(data, node, cmd);
	}
}

void	last_process(t_main *data, t_cmd_parse *node, char *cmd, int in)
{
	int	out;
	int	pid;
	int	fd[2];

	last_redir(data, node, &in, &out);
	if (in && node->hd_check == 0)
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

	data->hd_pos = 0;
	i = 0;
	in = 0;
	while (i < data->pipe_count)
	{
		pipe(fd);
		pipe_work(data, in, fd[1], node);
		close(fd[1]);
		in = fd[0];
		if (node->redirection)
		{
			if (node->redirection->operateur == LEFT_LEFT)
				data->hd_pos++;
		}
		node = node->next;
		i++;
	}
	data->pid_last = fork();
	if (data->pid_last == 0)
		last_process(data, node, cmd, in);
}

void	execute_cmd(t_main *data)
{
	t_cmd_parse	*node;
	int			i;
	char		*cmd;
	int			len;
	int			status;

	cmd = NULL;
	i = 0;
	node = data->cmd_parse;
	global_int = NULL;
	data->pipe_count = lstsize(node) - 1;
	if (first_builtins(data, node))
		return ;
	pipe_init(data, node);
	here_doc_init(data, node);
	if (global_int)
	{
		if (global_int[0] == -42)
		{
			global_int[0] = 0;
			return ;
		}
	}
	exec(data, node, cmd);
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
	if (data->hd_count)
		free(data->here_doc);
	if (data->cmd_paths)
		free_tab(data->cmd_paths);
}
