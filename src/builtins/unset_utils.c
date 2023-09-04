/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 07:53:22 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/09/03 04:06:26 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	copy_good_exp(t_main *data, char **tab)
{
	int	i;

	i = 0;
	while (data->env_exp[i])
		i++;
	free_tab(data->env_exp);
	data->env_exp = malloc(sizeof(char *) * i);
	if (!data->env_exp)
		error_mallc(data);
	i = 0;
	while (tab[i])
	{
		data->env_exp[i] = ft_strdup(tab[i]);
		i++;
	}
	data->env_exp[i] = 0;
	free_tab(tab);
}

void	copy_good_bis(t_main *data, char **tab)
{
	int	i;

	i = 0;
	while (data->env_bis[i])
		i++;
	free_tab(data->env_bis);
	data->env_bis = malloc(sizeof(char *) * i);
	if (!data->env_bis)
		error_mallc(data);
	i = 0;
	while (tab[i])
	{
		data->env_bis[i] = ft_strdup(tab[i]);
		i++;
	}
	data->env_bis[i] = 0;
	free_tab(tab);
}

char	**crt_exp(t_main *data, char **old_tab, char *s, int len)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (old_tab[i])
		i++;
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		error_mallc(data);
	i = 0;
	while (old_tab[i])
	{
		if (!ft_strncmp(old_tab[i], s, len + 11) && old_tab[i][len + 11] == '=')
			i++;
		else
			tab[j++] = ft_strdup(old_tab[i++]);
	}
	tab[j] = 0;
	return (tab);
}

char	**crt_bis(t_main *data, char **old_tab, char *s, int len)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (old_tab[i])
		i++;
	if (i == 1)
		return (NULL);
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		error_mallc(data);
	i = 0;
	while (old_tab[i])
	{
		if (!ft_strncmp(old_tab[i], s, len) && old_tab[i][len] == '=')
			i++;
		else
			tab[j++] = ft_strdup(old_tab[i++]);
	}
	tab[j] = 0;
	return (tab);
}
