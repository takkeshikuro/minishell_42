/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_sig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:38:28 by rmarecar          #+#    #+#             */
/*   Updated: 2023/09/01 20:29:44 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

t_main	*return_free_data(t_main *data)
{
	static t_main	*dr;

	if (data)
		dr = data;
	return (dr);
}

void	sig_hd(int signal)
{
	t_here_doc	*hd;
	int			i;
	int			hdc;
	t_main		*data;

	data = return_free_data(NULL);
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
		free(data->here_doc);
		free_tab(data->cmd_paths);
		free_kill(data);
		reset_stuff(data);
		exit (42);
	}
}

int	wait_hds(t_main *data, int i)
{
	int	status;

	status = 0;
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
	return (0);
}
