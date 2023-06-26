/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:12 by marecarraya       #+#    #+#             */
/*   Updated: 2023/06/26 19:57:06 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_outfile(t_cmd_parse *node)
{
	int	out;

	out = open(node->redirection->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (out == -1)
	{
		perror(node->redirection->str);
		exit(1);
	}
	return (out);
}

int	open_infile(t_cmd_parse *node)
{
	int	in;

	in = open(node->redirection->str, O_RDWR);
	if (in == -1)
	{
		perror(node->redirection->str);
		exit(1);
	}
	return (in);
}

int	open_append(t_cmd_parse *node)
{
	int	out;

	out = open(node->redirection->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (out == -1)
	{
		perror(node->redirection->str);
		exit(1);
	}
	return (out);
}
