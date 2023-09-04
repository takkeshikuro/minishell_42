/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:33:16 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/24 23:56:11 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_redirection(t_main *data, t_lexer *tmp, t_parser_data *p_data)
{
	char		*str_file;
	t_lexer		*new;
	int			id;
	int			id_next;

	str_file = ft_strdup(tmp->next->str);
	id = tmp->i;
	id_next = tmp->next->i;
	new = ft_lexernew(data, str_file, tmp->operateur);
	if (!new)
		exit (1);
	if (!p_data->redirection)
		p_data->redirection = new;
	else
		ft_lexeradd_back(&p_data->redirection, new);
	ft_lexerdelone(&p_data->lexer_list, id);
	ft_lexerdelone(&p_data->lexer_list, id_next);
	p_data->num_redir++;
}

void	redirection(t_main *data, t_parser_data *p_data)
{
	t_lexer	*tmp;

	tmp = p_data->lexer_list;
	while (tmp && !tmp->operateur)
		tmp = tmp->next;
	if (!tmp)
		return ;
	if (tmp->operateur)
	{
		if (tmp->operateur == PIPE)
			return ;
		else
			add_redirection(data, tmp, p_data);
	}
	redirection(data, p_data);
}
