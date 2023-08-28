/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_random.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 05:38:24 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/28 12:44:17 by tmorikaw         ###   ########.fr       */
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

int	pb_quote(const char *str, int sep)
{
	int	i;
	int ok;
	int comp;
	int sep1;
	int sep2;

	i = 0;
	ok = 0;
	comp = 0;
	sep1 = 34;
	sep2 = 39;
	while (str[i])
	{
		if (str[i] == sep1)
		{
			while (str[ok])
			{
				if (str[ok++] == sep1)
					comp++;
			}
			if (comp % 2 == 0)
				return (0);
			else
				return (error("should close quote."));
		}
		else if (str[i] == sep2)
		{
			while (str[ok])
			{
				if (str[ok++] == sep2)
					comp++;
			}
			if (comp % 2 == 0)
				return (0);
			else
				return (error("should close quote."));
		}
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

int	cmpchar(char c, char ok)
{
	if (c == ok)
		return (1);
	return (0);
}
