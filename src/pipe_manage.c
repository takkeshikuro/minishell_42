/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marecarrayan <marecarrayan@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:28:27 by marecarraya       #+#    #+#             */
/*   Updated: 2023/05/15 22:46:24 by marecarraya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	duplicate2(int input, int output)
{
	dup2(input, 0);
	close (input);
	dup2(output, 1);
	close(output);
}

void	child_process(t_main *data, char **envp, int pos)
{
	char	**string_command;
	int		fd;
	string_command = ft_split(data->input_line, '|');
	
	data->pipex->pid = fork();
	if (!(data->pipex->pid))
	{
		if (pos == 0 && data->pipe_count)
		{
			dup2(data->pipex->pipe_fd[1], 1);
			close(data->pipex->pipe_fd[1]);
		}
		else if (pos == data->pipe_count && data->pipe_count)
		{
			dup2(data->pipex->pipe_fd[2 * pos - 2], 0);
			close(data->pipex->pipe_fd[2 * pos - 2]);
		}
		else if (data->pipe_count && pos != 0 && data->pipe_count != pos)
			duplicate2(data->pipex->pipe_fd[2 * pos - 2], data->pipex->pipe_fd[2 * pos + 1]);
		data->pipex->cmd_args = ft_split(string_command[pos], ' ');
		data->pipex->cmd = get_command(data->pipex->cmd_paths, data->pipex->cmd_args[0]);
		if (!data->pipex->cmd)
		{
			printf("invalid input : %s\n", data->pipex->cmd_args[0]);
			free_tab(data->pipex->cmd_args);
			free(data->pipex->cmd);
			exit(1);
		}
		execve(data->pipex->cmd, data->pipex->cmd_args, envp);
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
	t_pipex	*test;
	
	data->pipex = test;
	pos = 0;
	pipe_init(data, env);
	while (pos <= data->pipe_count)
	{
		child_process(data, env, pos);
		pos++;
	}
	parent_free(data->pipex);
	waitpid(-1, NULL, 0);
}