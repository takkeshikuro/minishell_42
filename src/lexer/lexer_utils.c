/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 02:01:20 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/28 08:47:48 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ff_qt(char *str, int i, int j, int qt)
{
	j++;
	while (str[i + j] != qt && str[i + j])
	{
		j++;
		if (str[i + j] == qt && str[i + j + 1] == qt)
			j = (add_w_dig(str, i, j++));
	}
	j++;
	return (j);
}

int	add_word_support(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] && !is_space(str[i + j]) && !is_operateur(str[i + j]))
	{
		if (str[i + j] == 34)
		{
			j += ff_qt(str, i, j, 34);
			break ;
		}
		else if (str[i + j] == 39)
		{
			j += ff_qt(str, i, j, 39);
			break ;
		}
		else
			j++;
	}
	return (j);
}

int	different_add_w(char *s, int i, int nb_quote, int quote)
{
	int	j;
	int	ok;

	j = 0;
	ok = 1;
	while (s[i + j] && ok <= nb_quote)
	{
		if (s[i + j] == quote)
			ok++;
		j++;
	}
	return (j);
}

int	count_simp_quote(char *str, int i)
{
	int	simp;

	simp = 0;
	while (str[i])
	{
		if (str[i] == 32 && !simp)
			return (0);
		if (str[i] == 39)
		{
			if (str[i + 1] == 39)
				return (0);
			simp++;
		}
		i++;
	}
	return (simp);
}

int	count_doub_quote(char *str, int i)
{
	int	doub;

	doub = 0;
	while (str[i])
	{
		if (str[i] == 32 && !doub)
			return (0);
		if (str[i] == 34)
		{
			if (str[i + 1] == 34)
				return (0);
			else
				doub++;
		}
		i++;
	}
	return (doub);
}
