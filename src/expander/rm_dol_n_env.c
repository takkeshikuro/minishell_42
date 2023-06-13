/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_dol_n_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 02:57:58 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/13 03:00:24 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*copy_without_dol(t_cmd_parse *node, int i, char *s)
{
	int	j;
	int	k;

	k = 0;
	j = 0;
	while (node->cmd_tab[i][j] != '$')
	{
		s[k] = node->cmd_tab[i][j];
		j++;
		k++;
	}
	while (node->cmd_tab[i][j] && node->cmd_tab[i][j] != 32)
		j++;
	if (!node->cmd_tab[i][j])
		return (s);
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

int	check_env_variable(t_main *data, char *s)
{
	char	*str_dol;
	int		i;
	int		start_dol;
	int		size;
	int		result;

	i = 0;
	size = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (s[i + 1] == '\0')
		return (1);
	i++;
	start_dol = i;
	while (s[i] && s[i] != 32)
	{
		i++;
		size++;
	}
	str_dol = ft_substr(s, start_dol, (size - 1));
	result = check_env_bis(data->env_bis, str_dol);
	free(str_dol);
	return (result);
}