/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_random.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 05:38:24 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/20 02:21:33 by tmorikaw         ###   ########.fr       */
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
	int	nb_quote;

	i = 0;
	nb_quote = 0;
	while (str[i])
	{
		if (str[i] == sep)
			nb_quote += 1;
		i++;
	}
	if (nb_quote % 2 == 0)
		return (1);
	else
	{
		printf("minishell: need to close quote\n");
		return (0);
	}
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
