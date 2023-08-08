/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:24:58 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/08 16:37:43 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmpchar(char c, char ok)
{
	if (c == ok)
		return (1);
	return (0);
}

int	cp_s(char *tmp, char *s, int i)
{
	int		k;
	int		ok;

	k = 0;
	ok = 0;
	while (s[i] && s[i] != ' ')
	{
		if (ft_isalnum(s[i]) == 1)
			ok = 1;
		tmp[k++] = s[i++];
	}
	tmp[k] = '\0';
	return (ok);
}

int	syntax_dig_two(t_main *data, char *s, int i)
{
	char	*tmp;
	int		j;
	int		k;
	int		ok;

	if (cmpchar(s[i], ')'))
		return (syntax_err(data, "near unexpected token `)'"));
	else if (cmpchar(s[i], '\\'))
		return (syntax_err(data, "near unexpected token `\\'"));
	else if (cmpchar(s[i], '('))
		return (syntax_err(data, "should close parentheses"));
	else if (cmpchar(s[i], '/'))
	{
		j = i;
		k = 0;
		while (s[j] && s[j++] != ' ')
			k++;
		tmp = malloc(sizeof(char) * k + 1);
		if (!tmp)
			exit (1);
		ok = cp_s(tmp, s, i);
		return (is_dir_error(data, tmp, ok));
	}
}

int	syntax_dig(t_main *data, char *s)
{
	int		i;
	int		j;

	i = 0;
	if (cmpchar(s[0], '\'') || cmpchar(s[0], '"'))
		return (0);
	while (s[i])
	{
		if (cmpchar(s[i], '&'))
		{
			if (cmpchar(s[i + 1], '&'))
				return (syntax_err(data, "near unexpected token `&&'"));
			return (syntax_err(data, "near unexpected token `&'"));
		}
		else if (cmpchar(s[i], ';'))
		{
			if (cmpchar(s[i + 1], ';'))
				return (syntax_err(data, "near unexpected token `;;'"));
			return (syntax_err(data, "near unexpected token `;'"));
		}
		else if (syntax_dig_two(data, s, i))
			return (1);
		i++;
	}
	return (0);
}

int	syntax_check(t_main *data, int size)
{
	t_lexer	*current;
	int		i;

	i = 0;
	current = data->lexer_list;
	while (current)
	{
		if (current->str)
		{
			if (syntax_dig(data, current->str))
				return (1);
		}
		current = current->next;
	}
	return (0);
}