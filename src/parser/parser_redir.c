/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:33:16 by keshikuro         #+#    #+#             */
/*   Updated: 2023/06/04 18:10:52 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_redirection(t_lexer *tmp, t_parser_data *p_data)
{
	char		*str_file;
	t_lexer		*new;
	int			id;
	int			id_next;

	ft_putendl_fd("[check redir] adding redir", 1);
	str_file = ft_strdup(tmp->next->str);
	id = tmp->i;
	id_next = tmp->next->i;
	new = ft_lexernew(str_file, tmp->operateur);
	if (!new)
		exit (1);
	if (!p_data->redirection)
		p_data->redirection = new;
	else
		ft_lexeradd_back(&p_data->redirection, new);
	ft_lexerdelone(&p_data->lexer_list, id);
	ft_lexerdelone(&p_data->lexer_list, id_next);
	p_data->num_redir++;
}echo 

void	redirection(t_parser_data *p_data)
{
	t_lexer	*tmp;

	tmp = p_data->lexer_list;
	while (tmp && !tmp->operateur)
		tmp = tmp->next;
	if (!tmp)
		return ;
	ft_putendl_fd("[check redir] operateur found", 1);
	if (tmp->operateur)
	{
		if (tmp->operateur == PIPE)
			return ;
		else
			add_redirection(tmp, p_data);
		if (!tmp->next)
			return ;
	}
	redirection(p_data);
}