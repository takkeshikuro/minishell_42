/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:07:45 by keshikuro         #+#    #+#             */
/*   Updated: 2023/06/26 03:45:57 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	show_env_exp(t_main *data)
{
	int	i;

	i = 0;
	while (data->env_exp[i])
	{
		fprintf(stderr, "%s\n", data->env_exp[i]);
		i++;
	}
	data->return_value = 0;
	return (0);
}

void	add_to_bis(t_main *data, char *s)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (data->env_bis[i])
		i++;
	new_tab = malloc(sizeof(char *) * i + 2);
	if (!new_tab)
		exit (1);
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
	new_tab = malloc(sizeof(char *) * i + 2);
	if (!new_tab)
		exit (1);
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
	char **new_tab;
	int i;
	int j;

	i = 0;
	while (data->env_exp[i])
		i++;
	new_tab = malloc(sizeof(char *) * i + 1);
	if (!new_tab)
		exit (1);
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
	char **new_tab;
	int i;
	int j;

	i = 0;
	while (data->env_bis[i])
		i++;
	new_tab = malloc(sizeof(char *) * i + 1);
	if (!new_tab)
		exit (1);
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

char	*good_tmp(char *s)
{
	int	i;
	char *tmp;

	i = 0;
	while (s[i] != '=')
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	check_v_exist_exp(t_main *data, char *s)
{
	int i;
	int j;
	int k;
	char *name;

	i = 0;
	while (data->env_exp[i])
	{
		j = 11;
		k = 0;
		name = malloc(sizeof(char) * ft_strlen(data->env_exp[i]) - j);
		if (!name)
			exit (1);
		while (data->env_exp[i][j] != '=')
		{
			name[k] = data->env_exp[i][j];
			k++;
			j++;
		}
		name[k] = '\0';
		if ((ft_strlen(name) - ft_strlen(s)) == 0)
		{
			if (!ft_strncmp(name, s, ft_strlen(s)))
				return (i);
		}
		free(name);
		i++;
	}
	return (-1);
}

int	check_v_exist_bis(t_main *data, char *s)
{
	int	i;
	int size;

	i = 0;
	size = ft_strlen(s);
	while (data->env_bis[i])
	{
		if ((equal_env(data->env_bis[i]) - size) == 0)
		{
			if (!ft_strncmp(data->env_bis[i], s, size))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	print_error_export(char *s, int ok)
{
	int	i;

	i = 0;
	if (ok)
	{
		ft_putstr_fd("minishell: export: `", 2);
		while (s[i] && s[i] != '=')
			ft_putchar_fd(s[i++], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}
