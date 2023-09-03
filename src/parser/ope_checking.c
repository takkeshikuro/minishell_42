/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:34:46 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/28 08:37:59 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_l(t_main *data, t_lexer *crt)
{
	if (crt->next->operateur == RIGHT)
		return (syntax_err(data, "near unexpected token `newline'"));
	if (crt->next->operateur == LEFT && (!crt->next->next
			|| crt->next->next->operateur != LEFT))
		return (syntax_err(data, "near unexpected token `<'"));
	if (crt->next->operateur == LEFT_LEFT)
	{
		if (!crt->next->next || (crt->next->next->operateur != LEFT
				&& crt->next->next->operateur != LEFT_LEFT))
			return (syntax_err(data, "near unexpected token `<<'"));
		else if (crt->next->next && (crt->next->next->operateur == LEFT
				|| crt->next->next->operateur == LEFT_LEFT))
			return (syntax_err(data, "near unexpected token `<<<'"));
	}
	if (crt->next->operateur == RIGHT_RIGHT)
	{
		if (!crt->next->next || (crt->next->next->operateur != RIGHT
				&& crt->next->next->operateur != RIGHT_RIGHT))
			return (syntax_err(data, "near unexpected token `>'"));
		else if (crt->next->next->operateur == RIGHT
			|| crt->next->next->operateur == RIGHT_RIGHT)
			return (syntax_err(data, "near unexpected token `>>'"));
	}
	return (0);
}

int	check_r(t_main *data, t_lexer *crt)
{
	if (crt->next->operateur == LEFT)
		return (syntax_err(data, "near unexpected token `<'"));
	if (crt->next->operateur == RIGHT)
		return (syntax_err(data, "near unexpected token `>'"));
	if (crt->next->operateur == RIGHT_RIGHT)
		return (syntax_err(data, "near unexpected token `>>'"));
	if (crt->next->operateur == LEFT_LEFT)
	{
		if (!crt->next->next || (crt->next->next->operateur != LEFT
				&& crt->next->next->operateur != LEFT_LEFT))
			return (syntax_err(data, "near unexpected token `<<'"));
		else if (crt->next->next->operateur == LEFT
			|| crt->next->next->operateur == LEFT_LEFT)
			return (syntax_err(data, "near unexpected token `<<<'"));
	}
	return (0);
}

int	check_p_r(t_main *data, t_lexer *tmp)
{
	if (tmp->next->operateur == PIPE)
	{
		if (!tmp->next->next)
			return (syntax_err(data, "near unexpected token `newline'"));
		if (tmp->next->next->operateur == PIPE)
		{
			if (tmp->next->next->next
				&& tmp->next->next->next->operateur == PIPE)
				return (syntax_err(data, "near unexpected token `||'"));
			else
				return (syntax_err(data, "near unexpected token `|'"));
		}
	}
	return (0);
}

int	check_ll(t_main *data, t_lexer *crt)
{
	if (crt->next->operateur == PIPE)
	{
		if (crt->next->next && crt->next->next->operateur == PIPE)
			return (syntax_err(data, "near unexpected token `||'"));
		else
			return (syntax_err(data, "near unexpected token `|'"));
	}
	else if (crt->next->operateur == LEFT_LEFT)
	{
		if (!crt->next->next || (crt->next->next->operateur != LEFT
				&& crt->next->next->operateur != LEFT_LEFT))
			return (syntax_err(data, "near unexpected token `<'"));
		else if (crt->next->next->operateur == LEFT)
			return (syntax_err(data, "near unexpected token `<<'"));
		else if (crt->next->next->operateur == LEFT_LEFT)
			return (syntax_err(data, "near unexpected token `<<<'"));
	}
	return (0);
}

int	check_rr(t_main *data, t_lexer *crt)
{
	if (crt->next->operateur == PIPE)
	{
		if (crt->next->next && crt->next->next->operateur == PIPE)
			return (syntax_err(data, "near unexpected token `||'"));
		else
			return (syntax_err(data, "near unexpected token `|'"));
	}
	if (crt->next->operateur == RIGHT)
		return (syntax_err(data, "near unexpected token `>'"));
	if (crt->next->operateur == RIGHT_RIGHT)
		return (syntax_err(data, "near unexpected token `>>'"));
	return (0);
}
