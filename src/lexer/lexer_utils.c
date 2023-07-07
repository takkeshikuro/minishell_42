 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 05:13:10 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/29 04:26:26 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_word_support(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] && !is_space(str[i + j]) && !is_operateur(str[i + j]))
	{
		if (str[i + j] == 34)
		{
			j++;
			while (str[i + j] != 34 && str[i + j])
				j++;
			j++;
			break ;
		}
		else if (str[i + j] == 39)
		{
			j++;
			while (str[i + j] != 39 && str[i + j])
				j++;
			j++;
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
	int ok;

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
			simp++;
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
			doub++;
		i++;
	}
	return (doub);
}

void	rm_space(t_lexer *lst)
{
	t_lexer	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->str)
			tmp->str = ft_strtrim(tmp->str, " ");
		tmp = tmp->next;
	}
}
