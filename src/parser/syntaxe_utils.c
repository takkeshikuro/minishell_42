/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 08:44:48 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/28 08:45:22 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	if (cmpchar(s[i], ')'))
		return (syntax_err(data, "near unexpected token `)'"));
	else if (cmpchar(s[i], '\\'))
		return (syntax_err(data, "near unexpected token `\\'"));
	else if (cmpchar(s[i], '('))
		return (syntax_err(data, "should close parentheses"));
	return (0);
}

int	double_pipe(t_main *data, t_lexer *current)
{
	if (current->operateur == PIPE)
	{
		if (current->next->operateur == PIPE)
			return (syntax_err(data, "near unexpected token `||'"));
	}
	return (0);
}
