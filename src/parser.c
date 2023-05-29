/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:55:37 by keshikuro         #+#    #+#             */
/*   Updated: 2023/05/30 01:26:34 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_redirection(t_lexer *tmp, t_parser_data *p_data)
{
	char	*str_file;
	t_lexer *new;
	int	id;
	int id_next;
	
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
	p_data->num_redirection++;
}

void	redirection(t_parser_data *p_data)
{
	t_lexer	*tmp;
	
	tmp = p_data->lexer_list;
	while (tmp && !tmp->operateur)
		tmp = tmp->next;
	if (!tmp)
	{
		ft_putendl_fd("[check redir]no operateur found", 1);
		return ;
	}
	ft_putendl_fd("[check redir]operateur found", 1);
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

t_cmd_parse	*init_cmd(t_parser_data *p_data)
{
	char	**tab;
	t_lexer	*current;
	t_cmd_parse	*new_node;
	int		nb_word;
	int		i;

	i = 0;
	redirection(p_data);
	ft_putendl_fd("redir ok", 1);
	nb_word = count_words(p_data->lexer_list);
	tab = malloc(sizeof(char *) * nb_word);
	if (!tab)
		exit(1);
	current = p_data->lexer_list;
	while (nb_word > 0)
	{
		if (current->str)
		{
			tab[i] = ft_strdup(current->str);
			ft_lexerdelone(&p_data->lexer_list, current->i);
			current = p_data->lexer_list;
			i++;
		}
		nb_word--;
	}
	new_node = cmd_parse_new(tab,
			p_data->num_redirection, p_data->redirection);
	return (new_node);
}

int	go_parser(t_main *data)
{
	t_cmd_parse		*node;
	t_parser_data	parser_data;
	int				nb_pipe;

	data->cmd_parse = NULL;
	nb_pipe = count_pipe(data->input_line);
	small_check(data);
	while (data->lexer_list)
	{
		parser_data = init_p_data(data->lexer_list, data);
		node = init_cmd(&parser_data);
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
}
/////// IN PROGRESS ///////
// probleme a fix : pour une lexer list de 1 seul noeud,
// munmap_chunk() : invalid pointer pour le premier input apres execution de ./minishell

// fonction pour reset le id de lexer list