/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:58:15 by rmarecar          #+#    #+#             */
/*   Updated: 2023/09/01 20:37:09 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	close_error(int in, int out)
{
	if (in > 0)
		close (in);
	if (out > 1)
		close (out);
	return (-2);
}
int	redir_pipe(t_main *data, t_cmd_parse *node, int *in, int *out)
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
		if (*out == -2 || *in == -2)
		{
			node->redirection = tmp;
			return (close_error(*in, *out));
		}
		node->redirection = node->redirection->next;
	}
	node->redirection = tmp;
	return (0);
}

void	last_redir_hd(t_main *data, t_cmd_parse *node, int fd)
{
	node->hd_check = 1;
	close(fd);
	dup2(data->here_doc[data->hd_pos].fd[0], 0);
	close(data->here_doc[data->hd_pos].fd[0]);
}

int	last_redir2(t_main *data, t_cmd_parse *node, int *in, int *out)
{
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
	if (*out == -2 || *in == -2)
		return (close_error(*in, *out));
	return (0);
}

int	last_redir(t_main *data, t_cmd_parse *node, int *in, int *out)
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
		if (last_redir2(data, node, in, out) == -2)
		{
			node->redirection = tmp;
			return (-2);
		}
		node->redirection = node->redirection->next;
	}
	node->redirection = tmp;
	return (0);
}
