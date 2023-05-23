/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:51:08 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/23 06:07:33 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_parser_data	init_p_data(t_lexer *lexer_list, t_main *data)
{
	t_parser_data	parser_data;

	parser_data.lexer_list = lexer_list;
	parser_data.redirections = NULL;
	parser_data.num_redirections = 0;
	parser_data.data = data;
	return (parser_data);
}

void	small_check(t_main *data)
{
	t_lexer	*current;

	current = data->lexer_list;
	if (current->operateur == PIPE)
		exit(1); // error parsing
	while (current)
	{
		if (current->next == NULL)
		{
			if (current->operateur)
				exit(1); // error parsing
		}
		current = current->next;
	}
}

int	count_words(t_lexer *lexer_list)
{
	t_lexer	*current;
	int		nb;

	current = lexer_list;
	nb = 0;
	while (current)
	{
		if (current->str)
			nb += 1;
		if (current->next->operateur == PIPE)
			break ;
		current = current->next;
	}
	return (nb);
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
