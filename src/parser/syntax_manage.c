/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:24:58 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/28 09:10:29 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	syntax_slash(t_main *data, char *s)
{
	int		i;
	int		k;
	int		j;
	char	*tmp;
	int		ok;

	i = 0;
	while (s[i])
	{
		if (cmpchar(s[i], '/') && !cmpchar(s[i - 1], '.'))
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
		i++;
	}
	return (0);
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

int	syntax_c2(t_main *data, t_lexer *current)
{
	if (current->next && current->next->str)
	{
		if (syntax_slash(data, current->next->str))
			return (1);
	}
	else if (current->next && current->next->operateur)
	{
		if (double_pipe(data, current))
			return (1);
	}
	return (0);
}

int	syntax_check(t_main *data, int size)
{
	t_lexer	*current;
	int		i;

	i = 0;
	current = data->lexer_list;
	if (current->str)
		if (syntax_slash(data, current->str))
			return (1);
	while (current)
	{
		if (current->operateur)
		{
			if (syntax_c2(data, current))
				return (1);
		}
		else if (current->str)
			if (syntax_dig(data, current->str))
				return (1);
		current = current->next;
	}
	return (0);
}
