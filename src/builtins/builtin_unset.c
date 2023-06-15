/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:46 by keshikuro         #+#    #+#             */
/*   Updated: 2023/06/15 14:39:05 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	copy_good_tab(t_main *data, char **tab)
{
	int	i;

	i = 0;
	//free_tab(data->env_bis);
	while (tab[i])
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

char	**good_tab_creation(t_main *data, char *s, int len)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->env_bis[i])
		i++;
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		exit(0);
	i = 0;
	while (data->env_bis[i])
	{
		if (!ft_strncmp(data->env_bis[i], s, len))
			i++;
		else
		{
			tab[j] = ft_strdup(data->env_bis[i]);
			j++;
			i++;
		}
	}
	tab[j] = 0;
	return (tab);
}

int	built_unset(t_main *data, t_cmd_parse *cmd_parse)
{
	int i;
	int j;
	int len;
	char **tmp_tab;

	i = 1;
	while (cmd_parse->cmd_tab[i])
	{
		len = ft_strlen(cmd_parse->cmd_tab[i]);
		j = 0;
		while (data->env_bis[j])
		{
			if (!ft_strncmp(data->env_bis[j], cmd_parse->cmd_tab[i], len))
			{
				tmp_tab = good_tab_creation(data, cmd_parse->cmd_tab[i], len);
				copy_good_tab(data, tmp_tab);
				break ;
			}
			j++;
		}
		i++;
	}
	data->return_value = 0;	
	return (0);
}