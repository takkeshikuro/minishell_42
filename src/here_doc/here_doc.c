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
			close_free_hd(node, input, fd[1], j);
		if (!init_loop(node, input, fd))
			close_free_hd(node, input, fd[1], -42);
		write_hd(data, input, fd);
		j++;
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
