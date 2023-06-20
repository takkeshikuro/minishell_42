/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/06/20 01:53:30 by tmorikaw         ###   ########.fr       */
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

void	pipe_init(t_main *data, int count)
{
	int	i;

	i = 0;
	if (count)
	{
		data->pipe_fd = malloc(sizeof(int) * count * 2);
		if (!data->pipe_fd)
			return ;
		while (i < count)
		{
			if (pipe(data->pipe_fd + 2 * i) == -1)
				exit (1);
			i++;
		}
	}
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

void	pipe_redirect(t_main *data, int count, int pos)
{	
	if (pos == 0 && count)
		dup2(data->pipe_fd[1], 1);
	else if (pos == count && count)
	{
	//	write(2, "\nok\n", 3);
		dup2(data->pipe_fd[2 * pos - 2], 0);
	}else if (count && pos && pos != count)
	{
		dup2(data->pipe_fd[2 * pos - 2], 0);
		dup2(data->pipe_fd[2 * pos + 1], 1);
	}
	close_pipe(data, count);
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

void	duplicate2(int input, int output)
{
	dup2(input, 0);
	dup2(output, 1);
}

void	child_process(t_main *data, int pos, int count, t_cmd_parse *node)
{
	int		pid;
	char	*cmd;
	pid = fork();
	if (pid == 0)
	{
		pipe_redirect(data, count, pos);
		close_pipe(data, count);
		cmd = get_command(data->cmd_paths, node->cmd_tab[0]);
		//printf("\n%s\n", cmd);
		execve(cmd, node->cmd_tab, data->env_bis);
		exit(1);
	}
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

void	execute_cmd(t_main *data)
{
	int			count;
	int			pos;
	int			pid;
	t_cmd_parse	*node;

	node = data->cmd_parse;
	count = lstsize(data->cmd_parse) - 1;
	data->pipe_count = count;
	pos = 0;
	pipe_init(data, count);
	while (pos <= count)
	{
		child_process(data, pos, count, node);
		node = node->next;
		pos++;
	}
	close_pipe(data, count);
	waitpid(-1, NULL, 0);
	
	//wait_childs(count);
}