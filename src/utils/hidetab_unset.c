/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidetab_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 04:11:28 by keshikuro         #+#    #+#             */
/*   Updated: 2023/09/03 04:13:21 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	copy_good_hidetab(t_main *data, char **tab)
{
	int	i;

	i = 0;
	while (data->hidetab[i])
		i++;
	free_tab(data->hidetab);
	data->hidetab = malloc(sizeof(char *) * i);
	if (!data->hidetab)
		error_mallc(data);
	i = 0;
	while (tab[i])
	{
		data->hidetab[i] = ft_strdup(tab[i]);
		i++;
	}
	data->hidetab[i] = 0;
}

void	same_for_hidetab(t_main *data, char *s, int len)
{
	int		i;
	char	**tmp_tab;

	i = 0;
	if (!data->hidetab)
		return ;
	while (data->hidetab[i])
	{
		if (!ft_strncmp(data->hidetab[i], s, len)
			&& data->hidetab[i][len] == '=')
		{
			tmp_tab = crt_bis(data, data->hidetab, s, len);
			if (!tmp_tab)
				break ;
			copy_good_hidetab(data, tmp_tab);
			free_tab(tmp_tab);
			return ;
		}
		i++;
	}
	free_tab(data->hidetab);
	data->hidetab = NULL;
	return ;
}

int	cmpchar(char c, char ok)
{
	if (c == ok)
		return (1);
	return (0);
}
