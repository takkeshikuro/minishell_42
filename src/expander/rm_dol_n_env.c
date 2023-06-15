/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_dol_n_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 02:57:58 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/15 20:20:17 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*copy_without_dol(t_cmd_parse *node, int i, int j, char *s)
{
	int	k;

	k = 0;
	while (k < j)
	{
		s[k] = node->cmd_tab[i][k];
		k++;
	}
	while (node->cmd_tab[i][j] && node->cmd_tab[i][j] != 32)
		j++;
	if (!node->cmd_tab[i][j])
	{
		s[k] = '\0';
		return (s);
	}
	while (node->cmd_tab[i][j])
	{
		s[k] = node->cmd_tab[i][j];
		j++;
		k++;
	}
	s[k] = '\0';
	return (s);
}

int	check_env_bis(char **env, char *str_dol)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str_dol, ft_strlen(str_dol)))
			return (i);
		i++;
	}
	return (-1);
}

int	check_env_variable(t_main *data, char *s, int j)
{
	char	*str_dol;
	int		i;
	int		size;
	int		result;

	size = 0;
	if (s[j + 1] == '\0' || s[j + 1] == ' ')
		return (-2);
	if (s[j + 1] == '?')
		return (-3);
	i = j + 1;
	while (s[i] && s[i] != 32)
	{
		i++;
		size++;
	}
	str_dol = ft_substr(s, j + 1, (size - 1));
	result = check_env_bis(data->env_bis, str_dol);
	free(str_dol);
	return (result);
}
