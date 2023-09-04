/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:32:15 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/30 12:36:58 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_double(t_main *data, t_lexer *current)
{
	if (current->operateur == RIGHT_RIGHT)
	{
		if (check_rr(data, current))
			return (1);
	}
	else if (current->operateur == LEFT_LEFT)
	{
		if (check_ll(data, current))
			return (1);
	}
	return (0);
}

int	check_single(t_main *data, t_lexer *current)
{
	if (current->operateur == RIGHT)
	{
		if (check_p_r(data, current))
			return (1);
		else if (check_r(data, current))
			return (1);
	}
	else if (current->operateur == LEFT)
	{
		if (current->next->operateur == PIPE)
		{
			if (current->next->next && current->next->next->operateur == PIPE)
				return (syntax_err(data, "near unexpected token `||'"));
			else
				return (syntax_err(data, "near unexpected token `|'"));
		}
		else if (check_l(data, current))
			return (1);
	}
	return (0);
}

int	ope_check(t_main *data)
{
	t_lexer	*current;

	current = data->lexer_list;
	if (current->operateur == PIPE)
	{
		if (current->next && current->next->operateur == PIPE)
			return (syntax_err(data, "near unexpected token `||'"));
		else
			return (syntax_err(data, "near unexpected token `|'"));
	}
	while (current)
	{
		if (!current->next)
		{
			if (current->operateur > 1 && current->operateur < 6)
				return (syntax_err(data, "near unexpected token `newline'"));
			return (0);
		}
		if (check_double(data, current))
			return (1);
		else if (check_single(data, current))
			return (1);
		current = current->next;
	}
	return (0);
}

int	small_case(t_main *data, char *s)
{
	if (!ft_strncmp(s, "!", 1))
		data->return_value = 1;
	else if (!ft_strncmp(s, ":", 1))
		data->return_value = 0;
	return (1);
}

int	small_check(t_main *data)
{
	int				size;
	t_lexer			*tmp;

	tmp = data->lexer_list;
	size = lexer_size(data->lexer_list);
	if (syntax_check(data, size))
		return (1);
	if (var_check(data, data->lexer_list))
		return (1);
	while (tmp)
	{
		if (size == 1 && !tmp->operateur)
		{
			if ((!ft_strncmp(tmp->str, "!", 1) || !ft_strncmp(tmp->str, ":", 1))
				&& ft_strlen(tmp->str) == 1)
				return (small_case(data, tmp->str));
			else if (!ft_strncmp(tmp->str, ".", 1) && ft_strlen(tmp->str) == 1)
				return (error(data, ".: usage: . filename [arguments]", 2));
			else if (!ft_strncmp(tmp->str, "..", 2) && ft_strlen(tmp->str) == 2)
				return (error(data, "..: command not found", 127));
		}
		tmp = tmp->next;
	}
	return (0);
}
