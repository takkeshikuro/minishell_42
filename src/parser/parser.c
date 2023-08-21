/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:55:37 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/22 00:22:02 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd_parse	*cmd_parse_new(char **tab, int num_redir, t_lexer *redirection)
{
	t_cmd_parse	*new;

	new = (t_cmd_parse *)malloc(sizeof(t_cmd_parse));
	if (!new)
		exit(1);
	new->cmd_tab = tab;
	new->next = NULL;
	new->prev = NULL;
	new->builtin = NULL;
	new->redirection = redirection;
	new->num_redirection = num_redir;
	new->hd_file_name = NULL;
	return (new);
}

t_cmd_parse	*init_cmd(t_parser_data *p_data, int nb_word)
{
	char		**tab;
	t_lexer		*current;
	t_cmd_parse	*new_node;
	int			i;

	i = 0;
	redirection(p_data);
	nb_word = count_words(p_data->lexer_list);
	tab = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		exit(1);
	current = p_data->lexer_list;
	while (nb_word-- > 0)
	{
		if (current->str)
		{
			tab[i] = ft_strdup(current->str);
			ft_lexerdelone(&p_data->lexer_list, current->i);
			current = p_data->lexer_list;
			i++;
		}
	}
	tab[i] = 0;
	new_node = cmd_parse_new(tab, p_data->num_redir, p_data->redirection);
	return (new_node);
}

int	go_parser(t_main *data)
{
	t_cmd_parse		*node;
	t_parser_data	parser_data;
	int				nb;

	if (small_check(data) || ope_check(data))
		return (0);
	while (data->lexer_list)
	{
		parser_data = init_p_data(data->lexer_list, data);
		node = init_cmd(&parser_data, nb);
		if (!node)
			exit(1);
		if (!data->cmd_parse)
			data->cmd_parse = node;
		else
			cmd_parseadd_back(&data->cmd_parse, node);
		data->lexer_list = parser_data.lexer_list;
		if (data->lexer_list && data->lexer_list->operateur == PIPE)
			ft_lexerdelone(&data->lexer_list, data->lexer_list->i);
	}
	return (1);
}
