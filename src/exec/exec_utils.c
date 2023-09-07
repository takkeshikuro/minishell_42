/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/06/26 19:54:40 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	lstsize(t_cmd_parse *lst)
{
	int			size;
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

char	*get_command(t_main *data, char **paths, char *cmd)
{
	char	*command;
	char	*tmp;

	if (!paths || !cmd || !cmd[0])
		return (NULL);
	if (contains_char(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		if (access(cmd, X_OK))
			exit_access(data, cmd);
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

void	close_pipe(t_main *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (data->pipe_fd[i] > -1)
			close(data->pipe_fd[i]);
		i++;
	}
}
