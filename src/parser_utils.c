/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:51:08 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/25 05:14:26 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	parser_data.num_redirection = 0;
	parser_data.data = data;
	return (parser_data);
}

void	small_check(t_main *data)
{
	t_lexer	*current;

	current = data->lexer_list;
	if (current->operateur == PIPE)
		exit_bash_error("syntax error near unexpected token `|'");
	while (current)
	{
		if (current->next == NULL)
		{
			if (current->operateur)
				exit_bash_error("syntax error near unexpected token `newline'");
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
