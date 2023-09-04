/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_rm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:07:45 by keshikuro         #+#    #+#             */
/*   Updated: 2023/09/03 01:53:06 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	show_env_exp(t_main *data)
{
	int	i;

	i = 0;
	while (data->env_exp[i])
	{
		ft_putendl_fd(data->env_exp[i], 1);
		i++;
	}
	data->return_value = 0;
	return (1);
}

void	add_to_bis(t_main *data, char *s)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (data->env_bis[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		error_mallc(data);
	i = 0;
	while (data->env_bis[i])
	{
		new_tab[i] = ft_strdup(data->env_bis[i]);
		i++;
	}
	new_tab[i++] = ft_strdup(s);
	new_tab[i] = 0;
	free_tab(data->env_bis);
	data->env_bis = new_tab;
}

void	add_v_to_envexp(t_main *data, char *s)
{
	int		i;
	char	**new_tab;
	char	*tmp;

	i = 0;
	tmp = "declare -x ";
	while (data->env_exp[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		error_mallc(data);
	i = 0;
	while (data->env_exp[i])
	{
		new_tab[i] = ft_strdup(data->env_exp[i]);
		i++;
	}
	new_tab[i++] = ft_strjoin(tmp, s);
	new_tab[i] = 0;
	free_tab(data->env_exp);
	data->env_exp = new_tab;
}

void	rm_variable_exp(t_main *data, int supp)
{
	char	**new_tab;
	int		i;
	int		j;

	i = 0;
	while (data->env_exp[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	if (!new_tab)
		error_mallc(data);
	i = -1;
	while (++i < supp)
		new_tab[i] = ft_strdup(data->env_exp[i]);
	j = i;
	i += 1;
	while (data->env_exp[i])
	{
		new_tab[j] = ft_strdup(data->env_exp[i]);
		i++;
		j++;
	}
	new_tab[j] = 0;
	free_tab(data->env_exp);
	data->env_exp = new_tab;
}

void	rm_variable_bis(t_main *data, int supp)
{
	char	**new_tab;
	int		i;
	int		j;

	i = 0;
	while (data->env_bis[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	if (!new_tab)
		error_mallc(data);
	i = -1;
	while (++i < supp)
		new_tab[i] = ft_strdup(data->env_bis[i]);
	j = i;
	i += 1;
	while (data->env_bis[i])
	{
		new_tab[j] = ft_strdup(data->env_bis[i]);
		i++;
		j++;
	}
	new_tab[j] = 0;
	free_tab(data->env_bis);
	data->env_bis = new_tab;
}
