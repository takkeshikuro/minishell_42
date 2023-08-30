/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:39:03 by rmarecar          #+#    #+#             */
/*   Updated: 2023/08/30 15:45:04 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_free_hd(t_main *data, t_cmd_parse *node, char *input, int check)
{
	int	i;

	i = 0;
	if (check != -42)
	{
		fprintf(stderr, "bash: warning: here-document at line %d ", check);
		fprintf(stderr, "deliminited by end-of-file");
		fprintf(stderr, "(wanted `%s')\n", node->redirection->str);
	}
	free(input);
	while (i < data->hd_count)
	{
		if (data->here_doc[i].pos == 0)
			break ;
		close(data->here_doc[i].fd[0]);
		close(data->here_doc[i].fd[1]);
		i++;
	}
	exit (1);
}

void	write_hd(t_main *data, char *input, int fd[2])
{
	int	i;

	i = 0;
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
	free(input);
}
