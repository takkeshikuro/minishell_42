/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:58:15 by rmarecar          #+#    #+#             */
/*   Updated: 2023/08/08 14:33:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redir_pipe(t_main *data, t_cmd_parse *node, int *in, int *out)
{
	node->hd_check = 0;
	while (node->redirection)
	{
		if (node->redirection->operateur == RIGHT)
			*out = open_outfile(node);
		if (node->redirection->operateur == LEFT)
			*in = open_infile(node);
		if (node->redirection->operateur == RIGHT_RIGHT)
			*out = open_append(node);
		if (node->redirection->operateur == LEFT_LEFT)
		{
			node->hd_check = 1;
			dup2(data->here_doc[data->hd_pos].fd[0], 0);
			close(data->here_doc[data->hd_pos].fd[0]);
		}
		node->redirection = node->redirection->next;
	}
}

void	last_redir(t_main *data, t_cmd_parse *node, int *in, int *out)
{
	node->hd_check = 0;
	while (node->redirection)
	{
		if (node->redirection->operateur == RIGHT)
		{
			*out = open_outfile(node);
			dup2(*out, 1);
			close(*out);
		}
		if (node->redirection->operateur == LEFT)
			*in = open_infile(node);
		if (node->redirection->operateur == RIGHT_RIGHT)
		{
			*out = open_append(node);
			dup2(*out, 1);
			close(*out);
		}
		if (node->redirection->operateur == LEFT_LEFT)
		{
			node->hd_check = 1;
			dup2(data->here_doc[data->hd_pos].fd[0], 0);
			close(data->here_doc[data->hd_pos].fd[0]);
		}
		node->redirection = node->redirection->next;
	}
}
