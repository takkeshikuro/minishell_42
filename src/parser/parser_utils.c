/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:51:08 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/01 06:10:46 by keshikuro        ###   ########.fr       */
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

int	small_check(t_main *data)
{
	t_lexer *tmp;
	int		size;

	tmp = data->lexer_list;
	size = lexer_size(data->lexer_list);
	while (tmp)
	{
		if (size == 1 && !tmp->operateur)
		{
			if (!ft_strncmp(tmp->str, "!", 1) || !ft_strncmp(tmp->str, ":", 1))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

// A NORMER 
int	ope_check(t_main *data)
{
	t_lexer	*current;

	current = data->lexer_list;
	if (current->operateur == PIPE)
		return (syntax_err(data, "near unexpected token `|'"));
	while (current)
	{
		if (!current->next)
		{
			if (current->operateur > 1 && current->operateur < 6)
				return (syntax_err(data, "near unexpected token `newline'"));
			else
				return (0);
		}
		if (current->operateur == RIGHT_RIGHT)
		{
			if (current->next->operateur == RIGHT)
				return (syntax_err(data, "near unexpected token `>'"));
			if (current->next->operateur == RIGHT_RIGHT)
				return (syntax_err(data, "near unexpected token `>>'"));
		}
		if (current->operateur == LEFT_LEFT)
		{
			if (current->next->operateur == LEFT_LEFT)
			{
				if (!current->next->next || (current->next->next->operateur != LEFT && current->next->next->operateur != LEFT_LEFT))
					return (syntax_err(data, "near unexpected token `<'"));
				else if (current->next->next->operateur == LEFT)
					return (syntax_err(data, "near unexpected token `<<'"));
				else if (current->next->next->operateur == LEFT_LEFT)
					return (syntax_err(data, "near unexpected token `<<<'"));
			}
		}
		if (current->operateur == RIGHT)
		{
			if (current->next->operateur == LEFT)
				return (syntax_err(data, "near unexpected token `<'"));
			if (current->next->operateur == RIGHT)
				return (syntax_err(data, "near unexpected token `>'"));
			if (current->next->operateur == RIGHT_RIGHT)
				return (syntax_err(data, "near unexpected token `>>'"));
			if (current->next->operateur == LEFT_LEFT)
			{
				if (!current->next->next || (current->next->next->operateur != LEFT && current->next->next->operateur != LEFT_LEFT))
					return (syntax_err(data, "near unexpected token `<<'"));
				else if (current->next->next->operateur == LEFT || current->next->next->operateur == LEFT_LEFT)
					return (syntax_err(data, "near unexpected token `<<<'"));
			}
		}
		else if (current->operateur == LEFT)
		{
			if (current->next->operateur == RIGHT)
				return (syntax_err(data, "near unexpected token `newline'"));
			if (current->next->operateur == LEFT && (!current->next->next || current->next->next->operateur != LEFT))
				return (syntax_err(data, "near unexpected token `<'"));
			if (current->next->operateur == LEFT_LEFT)
			{
				if (!current->next->next || (current->next->next->operateur != LEFT && current->next->next->operateur != LEFT_LEFT))
					return (syntax_err(data, "near unexpected token `<<'"));
				else if (current->next->next && (current->next->next->operateur == LEFT || current->next->next->operateur == LEFT_LEFT))
					return (syntax_err(data, "near unexpected token `<<<'"));
			}
			if (current->next->operateur == RIGHT_RIGHT)
			{
				if (!current->next->next || (current->next->next->operateur != RIGHT && current->next->next->operateur != RIGHT_RIGHT))
					return (syntax_err(data, "near unexpected token `>'"));
				else if (current->next->next->operateur == RIGHT || current->next->next->operateur == RIGHT_RIGHT)
					return (syntax_err(data, "near unexpected token `>>'"));
			}
		}
		current = current->next;
	}
	return (0);
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
