/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:51:26 by marvin            #+#    #+#             */
/*   Updated: 2023/07/06 18:51:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_var_content(t_main *data, char *var_name)
{
	int		i;
	char	*content;
	char	**envp;
	char	**envp_exp;
	int		len;

	len = ft_strlen(var_name);
	i = 0;
	envp = data->env_bis;
	envp_exp = data->env_exp;
	while (envp[i])
	{
		if (!ft_strncmp(var_name, envp[i], len))
			return (envp[i] + len + 1);
		i++;
	}
	i = 0;
	while (envp_exp[i])
	{
		if (!ft_strncmp(var_name, envp_exp[i] + 11, len))
			return (envp_exp[i] + 12 + len);
		i++;
	}
	return (NULL);
}

int	init_loop(t_cmd_parse *node, char *input, int fd[2])
{
	int	size;

	size = ft_strlen(input);
	if (!ft_strncmp(input, node->redirection->str, size) && size)
	{
		close(fd[1]);
		return (0);
	}
	return (1);
}

int	here_doc_var(t_main *data, char *input, int i, int fd[2])
{
	char	*var_name;
	char	*var_content;
	int		len;

	var_name = get_var_name(input + i);
	var_content = get_var_content(data, var_name);
	if (var_content != NULL)
		write(fd[1], var_content, ft_strlen(var_content));
	len = ft_strlen(var_name) + 1;
	free(var_name);
	return (len);
}
int	*return_hd(int fd[2])
{
	static int	fd_hd[2];

	if (fd)
	{
		fd_hd[0] = fd[0];
		fd_hd[1] = fd[1];
	}
	return (fd_hd);
}

void	sig_hd(int signal)
{
	int	*fd;

	fd = return_hd(NULL);
	close(fd[1]);
	close(fd[0]);
	exit (42);
}

void	here_doc_manage(t_main *data, t_cmd_parse *node, int fd[2])
{
	char	*input;
	int		i;
	char	*var_name;
	char	*var_content;
	int		j;

	j = 0;
	signal(SIGINT, sig_hd);
	close(fd[0]);

	while (1)
	{
		i = 0;
		input = readline(">");
		if (!input)
		{
			fprintf(stderr, "bash: warning: here-document at line %d deliminited by end-of-file (wanted `%s')\n", j, node->redirection->str);
			free(input);
			close(fd[1]);
			break ;
		}
		if (!init_loop(node, input, fd))
		{
			free (input);
			close(fd[1]);
			break ;
		}
		while (input[i])
		{
			if (input[i] == '$' && input[i + 1] != ' ')
				i += here_doc_var(data, input, i, fd);
			else
			{
				write(fd[1], &input[i], 1);
				i++;
			}
		}
		write(fd[1], "\n", 1);
		j++;
		free(input);
	}
	exit(1);
}

void	here_doc_init(t_main *data, t_cmd_parse *node)
{
	int			i;
	int			pid;
	t_cmd_parse	*nodebis;
	int			status;
	int			*hd_fd;
	nodebis = node;
	i = 0;
	signal(SIGINT, SIG_IGN);
	while (i < data->hd_count)
	{
		pipe(data->here_doc[i].fd);
		hd_fd = return_hd(data->here_doc[i].fd);
		pid = fork();
		if (pid == 0)
			here_doc_manage(data, nodebis, data->here_doc[i].fd);
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 42)
		{
			// close(data->here_doc[i].fd[0]);
			// close(data->here_doc[i].fd[1]);
			while (i >= 0)
			{
				close(data->here_doc[i].fd[0]);
				close(data->here_doc[i].fd[1]);
				i--;
			}
			break ;
		}
		close(data->here_doc[i].fd[1]);
		if (!nodebis->cmd_tab[0])
			close(data->here_doc[i].fd[0]);
		i++;
		nodebis = nodebis->next;
	}
	signal(SIGINT, sig_handler);
}
