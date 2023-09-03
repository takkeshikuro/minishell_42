/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:51:08 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/08 13:36:50 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cmd_parseadd_back(t_cmd_parse **lst, t_cmd_parse *new)
{
	t_cmd_parse	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_parser_data	init_p_data(t_lexer *lexer_list, t_main *data)
{
	t_parser_data	parser_data;

	parser_data.lexer_list = lexer_list;
	parser_data.redirection = NULL;
	parser_data.num_redir = 0;
	parser_data.data = data;
	return (parser_data);
}

int	lexer_size(t_lexer *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

int	count_words(t_lexer *lexer_list)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = lexer_list;
	while (tmp && tmp->operateur != PIPE)
	{
		if (tmp->i >= 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	count_pipe(char *s)
{
	int	i;
	int	pipe;

	pipe = 0;
	i = 0;
	while (s[i])
	{
		if (i == '|')
			pipe += 1;
		i++;
	}
	return (pipe);
}
