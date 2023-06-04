/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:28:27 by marecarraya       #+#    #+#             */
/*   Updated: 2023/06/04 16:04:25 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	contains_char(char *str, char c)
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

void    close_pipe(t_main *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_count * 2)
	{
		close(data->pipex->pipe_fd[i]);
		i++;
	}
}

void	duplicate2(int input, int output)
{
	dup2(input, 0);
	dup2(output, 1);
}

void	child_process(t_main *data, char **envp, int pos)
{
	char	**string_command;
	pid_t	pid;
	int		status;

	status = 0;	
	pid = fork();
	if (pid == 0)
	{
		string_command = ft_split(data->input_line, '|');
		if (pos == 0 && data->pipe_count)
			dup2(data->pipex->pipe_fd[1], 1);
		else if (pos == data->pipe_count && data->pipe_count)
			dup2(data->pipex->pipe_fd[2 * pos - 2], 0);
		else if (data->pipe_count && pos != 0 && data->pipe_count != pos)
			duplicate2(data->pipex->pipe_fd[2 * pos - 2], data->pipex->pipe_fd[2 * pos + 1]);
		close_pipe(data);
		data->pipex->cmd_args = ft_split(string_command[pos], ' ');
		free_tab(string_command);
		data->pipex->cmd = get_command(data->pipex->cmd_paths, data->pipex->cmd_args[0]);
		if (!data->pipex->cmd)
		{
			printf("invalid input : %s\n", data->pipex->cmd_args[0]);
			free_tab(data->pipex->cmd_args);
			parent_free(data->pipex);
			free(data->pipex->cmd);
			exit(1);
		}
		execve(data->pipex->cmd, data->pipex->cmd_args, envp);
		exit (1);
	}
}
void	wait_childs(t_main *data)
{
	int	i;

	i = 0;
	while (i <= data->pipe_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

void	pipe_init(t_main *data, char **env)
{
	int	i;

	i = 0;
	data->pipex->pipe_fd = malloc(sizeof(int) * data->pipe_count * 2);
	if (!data->pipex->pid)
		return ;
	while (i < data->pipe_count)
	{
		if (pipe(data->pipex->pipe_fd + 2 * i) == -1)
			exit (1);
		i++;
	}
	data->pipex->paths = find_path(env);
	data->pipex->cmd_paths = ft_split(data->pipex->paths, ':');
}

void    parent_free(t_pipex *pipex)
{
	int i;

	i = 0;
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
	free(pipex->pipe_fd);
}

void	pipe_manage(t_main *data, char **env)
{
	int	pos;
	int	pid;
	t_pipex	*test;
	
	data->pipex = test;
	pos = 0;
	pipe_init(data, env);
	while (pos <= data->pipe_count)
	{
		child_process(data, env, pos);
		pos++;
	}
	close_pipe(data);
	waitpid(-1, NULL, 0);
	parent_free(data->pipex);
	return ;
}