/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/06/26 20:57:00 by rmarecar         ###   ########.fr       */
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
				hd = 1;
				pipe(fd);
				here_doc_manage(data, node, fd);
				close(fd[1]);
				dup2(fd[0], 0);
				close(fd[0]);
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

int	has_variable(char *input)
{
	int	i;

	i = 0;
	while(input[i])
	{
		if (input[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_varname_len(char *str)
{
	int	len;
	
	len = 1;
	while (str[len] > ' ' && str[len] < 127 && str[len] != '$')
		len++;
	return(len - 1);
}

char	*get_var_name(char *input)
{
	int		i;
	int		len;
	char	*name;

	i = 1;
	len = ft_varname_len(input);
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
	{
		fprintf(stderr, "ERROR MALLOC : GET VAR NAME (here_doc manage)");
		exit (1);
	}
	len = 0;
	while (input[i] != '$' && input[i] > ' '  && input[i] < 127)
	{
		name[len] = input[i];
		i++;
		len++;
	}
	name[len] = 0;
	return (name);
}

char	*get_var_content(t_main *data, char *var_name)
{
	int		i;
	char	*content;
	char	**envp;
	int		len;

	len = ft_strlen(var_name);
	i = 0;
	envp = data->env_bis;
	while (envp[i])
	{
		if (!ft_strncmp(var_name, envp[i], len))
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	here_doc_manage(t_main *data, t_cmd_parse *node, int fd[2])
{
	char	*input;
	int		size;
	int		i;
	char	*var_name;
	char	*var_content;

	while (1)
	{
		i = 0;
		input = readline(">");
		size = ft_strlen(input);
		if (!ft_strncmp(input, node->redirection->str, size))
			break ;
		while (input[i])
		{
			if (input[i] == '$' && input[i + 1] != ' ')
			{
				var_name = get_var_name(input + i);
				var_content = get_var_content(data, var_name);
				write(fd[1], var_content, ft_strlen(var_content));
				i += ft_strlen(var_name) + 1;
				free(var_name);
			}
			else
			{
				write(fd[1], &input[i], 1);
				i++;
			}
		}
		write(fd[1], "\n", 1);
	}
}

void	last_process(t_main *data, t_cmd_parse *node, char *cmd, int in)
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
			pipe(fd);
			here_doc_manage(data, node, fd);
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
		}
		node->redirection = node->redirection->next;
	}
	if (in && hd == 0)
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
