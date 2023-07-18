/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/07/18 19:09:48 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipe_init(t_main *data, t_cmd_parse *node)
{
	t_cmd_parse	*tmp;

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
	exit(127);
}

void	redir_pipe(t_main *data, t_cmd_parse *node, int *in, int *out)
{
	while (node->redirection)
	{
		if (node->redirection->operateur == RIGHT)
			*out = open_outfile(node);
		if (node->redirection->operateur == LEFT)
			*in = open_infile(node);
		if (node->redirection->operateur == RIGHT_RIGHT)
			*out = open_append(node);
		if (node->redirection->operateur == LEFT_LEFT)
		{
			node->hd_check = 1;
			dup2(data->here_doc[data->hd_pos].fd[0], 0);
			close(data->here_doc[data->hd_pos].fd[0]);
		}
		node->redirection = node->redirection->next;
	}
}

void	pipe_work(t_main *data, int in, int out, t_cmd_parse *node)
{
	pid_t	pid;
	char	*cmd;
	int		fd[2];
	int		hd;

	hd = 0;
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
		if (cmd == NULL)
			no_command(data, node);
		execve(cmd, node->cmd_tab, data->env_bis);
		exit(1);
	}
}

void	last_redir(t_main *data, t_cmd_parse *node, int *in, int *out)
{
	while (node->redirection)
	{
		if (node->redirection->operateur == RIGHT)
		{
			*out = open_outfile(node);
			dup2(*out, 1);
			close(*out);
		}
		if (node->redirection->operateur == LEFT)
			*in = open_infile(node);
		if (node->redirection->operateur == RIGHT_RIGHT)
		{
			*out = open_append(node);
			dup2(*out, 1);
			close(*out);
		}
		if (node->redirection->operateur == LEFT_LEFT)
		{
			node->hd_check = 1;
			dup2(data->here_doc[data->hd_pos].fd[0], 0);
			close(data->here_doc[data->hd_pos].fd[0]);
		}
		node->redirection = node->redirection->next;
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
	if (node->cmd_tab[0])
	{
		if (data->pipe_count == 0 && contains_char(node->cmd_tab[0], '=')
			&& node->cmd_tab[0][0] != '=')
		{
			add_v_to_envexp(data, node->cmd_tab[0]);
			return ;
		}
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
	data->pipe_count = lstsize(node) - 1;
	if (first_builtins(data, node))
		return ;
	pipe_init(data, node);
	here_doc_init(data, node);
	exec(data, node, cmd);
	waitpid(data->pid_last, &status, 0);
	while (i < data->pipe_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	if (WIFEXITED(status))
		data->return_value = WEXITSTATUS(status); 
	if (data->hd_count)
		free(data->here_doc);
}
