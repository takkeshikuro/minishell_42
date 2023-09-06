/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidetab_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 02:35:39 by keshikuro         #+#    #+#             */
/*   Updated: 2023/09/03 03:21:03 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_bis(t_main *data, char *s)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (data->hidetab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		error_mallc(data);
	i = 0;
	while (data->hidetab[i])
	{
		new_tab[i] = ft_strdup(data->hidetab[i]);
		i++;
	}
	new_tab[i++] = ft_strdup(s);
	new_tab[i] = 0;
	free_tab(data->hidetab);
	data->hidetab = new_tab;
}

void	add_v_to_hidetab(t_main *data, char *s)
{
	if (!data->hidetab)
	{
		data->hidetab = malloc(sizeof(char *) * 2);
		if (!data->hidetab)
			error_mallc(data);
		data->hidetab[0] = ft_strdup(s);
		data->hidetab[1] = 0;
		return ;
	}
	add_bis(data, s);
}

int	check_ht(t_main *data, char *s, int j)
{
	int		i;
	int		size;
	int		len;
	char	*str_dol;

	i = j + 1;
	size = 0;
	while (s[i] && s[i] != 32 && s[i] != '$')
	{
		i++;
		size++;
	}
	str_dol = ft_substr(s, j + 1, size);
	len = ft_strlen(str_dol);
	i = 0;
	while (data->hidetab[i])
	{
		if (!ft_strncmp(data->hidetab[i], str_dol, len)
			&& data->hidetab[i][len] == '=')
			break ;
		i++;
	}
	free(str_dol);
	return (i);
}

int	expand_from_hidetab(t_main *data, t_cmd_parse *node, int i, int j)
{
	int		nb_env;
	int		ok;
	char	*str_replace;

	nb_env = check_ht(data, node->cmd_tab[i], j);
	if (node->cmd_tab[i][j] == '$')
	{
		str_replace = keep_good_str(data->hidetab, nb_env);
		copy_past(node, i, j, str_replace);
		ok = ft_strlen(str_replace);
		free(str_replace);
		return (ok);
	}
	return (1);
}

int	check_hidetab(char **tab, char *s)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	if (!tab)
		return (-1);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], s, len) && tab[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
