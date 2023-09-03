/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_dol_n_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 02:57:58 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/09/03 02:37:41 by keshikuro        ###   ########.fr       */
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
	while (node->cmd_tab[i][j] && node->cmd_tab[i][j] != 32
		&& node->cmd_tab[i][j] != 39)
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

int	check_qt(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i + 1] == '\0' || s[i + 1] == 32)
		{
			if (s[i] == 39)
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_env_bis(char **env, char **hide, char *str_dol)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str_dol);
	if (check_hidetab(hide, str_dol) >= 0)
		return (888);
	if (!check_qt(str_dol))
	{
		while (env[i])
		{
			if (!ft_strncmp(env[i], str_dol, len) && env[i][len] == '=')
				return (i);
			i++;
		}
		return (-1);
	}
	while (env[i])
	{
		if (!ft_strncmp(env[i], str_dol, len - 1) && env[i][len - 1] == '=')
			return (999);
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
	if (size == 1)
		str_dol = ft_substr(s, j + 1, size);
	else
		str_dol = ft_substr(s, j + 1, size);
	result = check_env_bis(data->env_bis, data->hidetab, str_dol);
	free(str_dol);
	return (result);
}
