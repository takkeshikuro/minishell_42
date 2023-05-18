/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 05:38:24 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/18 23:36:46 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	error(char *s)
{
	printf("error : %s\n", s);
	exit(1);
}

void	void_error(char *s)
{
	printf("error : %s\n", s);
	return ;
}
