/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_random.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 05:38:24 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/30 12:46:50 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '\0')
		return (0);
	else
		return (1);
}

int	pb_quote_dig(t_main *data, char *s, int sep)
{
	int	ok;
	int	comp;

	ok = 0;
	comp = 0;
	while (s[ok])
	{
		if (s[ok++] == sep)
			comp++;
	}
	if (comp % 2 == 0)
		return (0);
	else
	{
		data->return_value = 2;
		return (error(data, "should close quote.", 2));
	}
}

int	pb_quote(t_main *data, char *str, int sep1, int sep2)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == sep1)
			return (pb_quote_dig(data, str, sep1));
		else if (str[i] == sep2)
			return (pb_quote_dig(data, str, sep2));
		i++;
	}
	return (0);
}

int	is_space(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_nbstr(char const *str, char sep)
{
	int	i;
	int	nbword;

	i = 0;
	nbword = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
			nbword++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (nbword);
}
