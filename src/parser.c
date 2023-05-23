/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:55:37 by keshikuro         #+#    #+#             */
/*   Updated: 2023/05/23 06:08:24 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	no_pipe(t_main *data, int size)
{
	t_lexer			*current;
	command_parse	*parser;

	parser->cmd_tab = malloc(sizeof(char *));
	if (!parser->cmd_tab)
		exit(1);
	current = data->lexer_list;
	while (current->next != NULL)
	{
		if (current->str)
		{
			//if (!ft_strncmp(data->tab_input_blank[0], ))
			// case of builtin
			//if (redirecction)
			// case of redirection
			else ft_strjoin(parser->cmd_tab[0], current->str);
		}
		else
			current = current->next;
	}
}

void	split_on_pipe(t_main *data)
{
	int			i_tab;
	int			nb_pipe;
	t_cmd_parse	*parser;
	t_lexer		*current;

	i_tab = 0;
	nb_pipe = count_pipe(data->input_line);
	parser->cmd_tab = malloc(sizeof(char *) * nb_pipe + 1);
	if (!parser->cmd_tab)
		exit(1);
	current = data->lexer_list;
	while (parser->cmd_tab[i_tab])
	{
		while (current->next != NULL)
		{
			if (current->str)
			{
				ft_strjoin(parser->cmd_tab[i_tab], current->str);
				if (current->next->str)
					ft_strjoin(parser->cmd_tab[i_tab], " ");
				else
					break ;
			}
			else if (current->operateur && current->operateur != PIPE)
				//redirection
				current = current->next;
		}
		i_tab++;
	}
}

// ft_lexerdelone(lexer_list, int i)
//ft_cmd_parse_new(**str, num redirection, redirection)
t_cmd_parse	cmd_parse_new(char **tab, )
{
	
}

t_cmd_parse	*init_cmd(t_parser_data *p_data)
{
	char			**tab;
	t_lexer			*current;
	int				nb_word;
	int				i;

	i = 0;
	nb_word = count_words(p_data->lexer_list);
	tab = malloc(sizeof(char *) * nb_word);
	if (!tab)
		exit (1);
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
	return (cmd_parse_new(tab, ));
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
			exit (1);
		if (!data->cmd_parse)
			data->cmd_parse = node;
		else
			cmd_parseadd_back();
		data->lexer_list = parser_data.lexer_list;
	}
}
/////// IN PROGRESS