/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:58:15 by rmarecar          #+#    #+#             */
/*   Updated: 2023/09/01 17:13:43 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redir_pipe(t_main *data, t_cmd_parse *node, int *in, int *out)
{
	t_lexer	*tmp;

	node->hd_check = 0;
	tmp = node->redirection;
	while (node->redirection)
	{
		if (node->redirection->operateur == RIGHT)
			*out = open_outfile(data, node, *out);
		if (node->redirection->operateur == LEFT)
			*in = open_infile(data, node, *in);
		if (node->redirection->operateur == RIGHT_RIGHT)
			*out = open_append(data, node, *out);
		if (node->redirection->operateur == LEFT_LEFT)
		{
			node->hd_check = 1;
			dup2(data->here_doc[data->hd_pos].fd[0], 0);
			close(data->here_doc[data->hd_pos].fd[0]);
		}
		node->redirection = node->redirection->next;
	}
	node->redirection = tmp;
}

void	last_redir_hd(t_main *data, t_cmd_parse *node, int fd)
{
	node->hd_check = 1;
	close(fd);
	dup2(data->here_doc[data->hd_pos].fd[0], 0);
	close(data->here_doc[data->hd_pos].fd[0]);
}

void	last_redir(t_main *data, t_cmd_parse *node, int *in, int *out)
{
	t_lexer	*tmp;

	node->hd_check = 0;
	tmp = node->redirection;
	while (node->redirection)
	{
		if (node->redirection->operateur == RIGHT)
		{
			*out = open_outfile(data, node, *out);
			dup2(*out, 1);
			close(*out);
		}
		if (node->redirection->operateur == LEFT)
		{
			*in = open_infile(data, node, *in);
		}
		if (node->redirection->operateur == RIGHT_RIGHT)
		{
			*out = open_append(data, node, *out);
			dup2(*out, 1);
			close(*out);
		}
		if (node->redirection->operateur == LEFT_LEFT)
		{
			if (node->hd_check != 1)
				last_redir_hd(data, node, *in);
		}
		node->redirection = node->redirection->next;
	}
	node->redirection = tmp;
}
