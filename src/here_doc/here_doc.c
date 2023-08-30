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

t_here_doc	*return_hd(t_here_doc *here_doc)
{
	static t_here_doc	*hd;
	if (here_doc)
		hd = here_doc;
	return (hd);
}

int	return_hd_count(int hd_count)
{
	static int	hdc;

	if (hd_count != -1)
		hdc = hd_count;
	return (hdc);
}

void	sig_hd(int signal)
{
	t_here_doc	*hd;
	int			i;
	int			hdc;

	if (signal == SIGINT)
	{
		i = 0;
		hd = return_hd(NULL);
		hdc = return_hd_count(-1);
		while (i < hdc)
		{
			if (hd[i].pos == 0)
				break ;
			close(hd[i].fd[0]);
			close(hd[i].fd[1]);
			i++;
		}
		exit (42);
	}
}

void	here_doc_manage(t_main *data, t_cmd_parse *node, int fd[2])
{
	char	*input;
	int		j;

	j = 0;
	signal(SIGINT, sig_hd);
	close(fd[0]);
	while (1)
	{
		input = readline(">");
		if (!input)
			close_free_hd(data, node, input, j);
		if (!init_loop(node, input, fd))
			close_free_hd(data, node, input, -42);
		write_hd(data, input, fd);
		j++;
	}
	exit(1);
}

int	here_doc_init(t_main *data, t_cmd_parse *node)
{
	int			i;
	int			pid;
	t_cmd_parse	*nodebis;
	int			status;

	nodebis = node;
	i = 0;
	return_hd(data->here_doc);
	return_hd_count(data->hd_count);
	signal(SIGINT, SIG_IGN);
	while (i < data->hd_count)
	{
		pipe(data->here_doc[i].fd);
		data->here_doc[i].pos = 1;
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
			signal(SIGINT, sig_handler);
			return (42);
		}
		close(data->here_doc[i].fd[1]);
		i++;
		nodebis = nodebis->next;
	}
	signal(SIGINT, sig_handler);
	return (0);
}
