/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 07:53:22 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/07/07 08:14:55 by tmorikaw         ###   ########.fr       */
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
		exit(1);
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
	//free_tab(data->env_bis);
	while (data->env_bis[i])
		i++;
	data->env_bis = malloc(sizeof(char *) * i);
	if (!data->env_bis)
		exit(1);
	i = 0;
	while (tab[i])
	{
		data->env_bis[i] = ft_strdup(tab[i]);
		i++;
	}
	data->env_bis[i] = 0;
	free_tab(tab);
}

char	**crt_exp(char **old_tab, char *s, int len)
{
	char	**tab;
	char	*test;
	int		i;
	int		j;

	i = 0;
	j = 0;
	test = ft_strjoin("declare -x ", s);
	while (old_tab[i])
		i++;
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		exit(0);
	i = 0;
	while (old_tab[i])
	{	
		if (!ft_strncmp(old_tab[i], test, len + 11))
			i++;
		else
			tab[j++] = ft_strdup(old_tab[i++]);
	}
	tab[j] = 0;
	return (tab);
}

char	**crt_bis(char **old_tab, char *s, int len)
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
		exit(0);
	i = 0;
	while (old_tab[i])
	{	
		if (!ft_strncmp(old_tab[i], s, len))
			i++;
		else
			tab[j++] = ft_strdup(old_tab[i++]);
	}
	tab[j] = 0;
	return (tab);
}
