/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 02:12:16 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/25 23:06:11 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	copy_name(t_main *data, char *tmp, int i)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (data->env_bis[i][j] != '=')
	{
		tmp[j] = data->env_bis[i][j];
		j++;
		k++;
	}
	tmp[k++] = '=';
	tmp[k++] = '"';
	j++;
	while (data->env_bis[i][j])
	{
		tmp[k] = data->env_bis[i][j];
		j++;
		k++;
	}
	tmp[k++] = '"';
	return (k);
}

void	copy_env(t_main *data, char *decla)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	i = 0;
	while (data->env_bis[i])
	{
		j = 0;
		size = ft_strlen(data->env_bis[i]);
		tmp = malloc(sizeof(char) * (size + 2) + 1);
		if (!tmp)
			error_mallc(data);
		j += copy_name(data, tmp, i);
		tmp[j] = '\0';
		data->env_exp[i] = ft_strjoin(decla, tmp);
		free(tmp);
		i++;
	}
	data->env_exp[i] = 0;
}

void	get_env_export(t_main *data)
{
	int		i;
	char	*decla;

	i = 0;
	decla = "declare -x ";
	while (data->env_bis[i])
		i++;
	data->env_exp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->env_exp)
		error_mallc(data);
	i = 0;
	copy_env(data, decla);
}

void	get_env(t_main *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env_bis = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->env_bis)
		error_mallc(data);
	i = 0;
	while (env[i])
	{
		data->env_bis[i] = ft_strdup(env[i]);
		i++;
	}
	data->env_bis[i] = 0;
}
