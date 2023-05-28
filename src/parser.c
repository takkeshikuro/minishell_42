/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:55:37 by keshikuro         #+#    #+#             */
/*   Updated: 2023/05/28 17:04:41 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_redirection(t_lexer *tmp, t_parser_data *p_data)
{
	t_lexer *new;

	new = ft_lexernew(tmp->str, tmp->operateur);
	if (!new)
		exit (1);
	ft_lexeradd_back(&p_data->redirection, new);
	
}

void	redirection(t_parser_data *p_data)
{
	t_lexer	*tmp;

	tmp = p_data->lexer_list;
	while (tmp)
	{
		if (tmp->operateur)
		{
			if (tmp->operateur == PIPE)
				return ;
		}
		else if (tmp->operateur >= 2 && tmp->operateur <= 5)
			add_redirection(tmp, p_data);
		tmp = tmp->next;
		if (!tmp)
			return ;
	}
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
	new->redirections = redirection;
	new->num_redirections = num_redir;
	new->hd_file_name = NULL;
	return (new);
}

t_cmd_parse	*init_cmd(t_parser_data *p_data)
{
	char	**tab;
	t_lexer	*current;
	int		nb_word;
	int		i;

	i = 0;
	
	//fucnton for rm redirection of lexer list
	redirection(p_data);
	nb_word = count_words(p_data->lexer_list);
	tab = malloc(sizeof(char *) * nb_word);
	if (!tab)
		exit(1);
	current = p_data->lexer_list;
	while (nb_word > 0)
	{
		if (current->str)
		{
			tab[i++] = ft_strdup(current->str);
			ft_lexerdelone(&p_data->lexer_list, current->i);
			current = p_data->lexer_list;
		}
		nb_word--;
	}
	return (cmd_parse_new(tab,
			p_data->num_redirection, p_data->redirection));
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
	}
}
/////// IN PROGRESS ///////