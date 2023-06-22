/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/06/14 13:39:11 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			return (envp[i] + 5);
		i++;
	}
	return (" ");
}

int	lstsize(t_cmd_parse *lst)
{
	int	size;
	t_cmd_parse	*lsts;

	lsts = lst;
	size = 0;
	while (lsts != NULL)
	{
		lsts = lsts->next;
		size++;
	}
	return (size);
}

void	pipe_init(t_main *data)
{
	data->path = find_path(data->env_bis);
	data->cmd_paths = ft_split(data->path, ':');
}

void	close_pipe(t_main *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(data->pipe_fd[i]);
		i++;
	}
}

int		contains_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*get_command(char **paths, char *cmd)
{
	char	*command;
	char	*tmp;

	if (!paths || !cmd)
		return (NULL);
	
	if (contains_char(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	wait_childs(int count)
{
	int	i;

	i = 0;
	while (i <= count)
	{
		write(2, "- ", 2);
		waitpid(-1, NULL, 0);
		i++;
	}
}

void	pipe_work(t_main *data, int in, int out, t_cmd_parse *node)
{
	pid_t	pid;
	char	*cmd;

	pid = fork();
	if (pid == 0)
	{
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
		{
			write(2, node->cmd_tab[0], ft_strlen(node->cmd_tab[0]));
			write(2, ": command not found\n", 20);
			exit(1);
		}
		execve(cmd, node->cmd_tab, data->env_bis);
		exit(1);
	}
}

void	execute_cmd(t_main *data)
{
	int			pid;
	t_cmd_parse	*node;
	int			in;
	int			fd[2];
	int			i;
	char		*cmd;

	node = data->cmd_parse;
	data->pipe_count = lstsize(data->cmd_parse) - 1;
	i = 0;
	in = 0;
	pipe_init(data);
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
	{
		if (in)
			dup2(in, 0);

		cmd = get_command(data->cmd_paths, node->cmd_tab[0]);
		if (cmd == NULL)
		{
			write(2, node->cmd_tab[0], ft_strlen(node->cmd_tab[0]));
			write(2, ": command not found\n", 20);
			exit(1);
		}
		execve(cmd, node->cmd_tab, data->env_bis);
		exit (1);
	}
	i = 0;
	while (i <= data->pipe_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}