/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:37:29 by keshikuro         #+#    #+#             */
/*   Updated: 2023/06/26 16:02:15 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_v_exist_exp(t_main *data, char *s)
{
	int		i;
	int		j;
	int		k;
	char	*name;

	i = 0;
	while (data->env_exp[i])
	{
		j = 11;
		k = 0;
		name = malloc(sizeof(char) * ft_strlen(data->env_exp[i]) - j + 1);
		if (!name)
			error_mallc(data);
		while (data->env_exp[i][j] && data->env_exp[i][j] != '=')
			name[k++] = data->env_exp[i][j++];
		name[k] = '\0';
		if ((ft_strlen(name) - ft_strlen(s)) == 0)
		{
			if (!ft_strncmp(name, s, ft_strlen(s)))
				return (free(name), i);
		}
		free(name);
		i++;
	}
	return (-1);
}

int	check_v_exist_bis(t_main *data, char *s)
{
	int		i;
	int		size;

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
