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

int	rm_dollard(t_main *data, t_cmd_parse *cmd_node, int i, int j)
{
	int		size_dol;
	char	*new_s;
	int		diff;
	int		tmp_j;

	size_dol = 0;
	tmp_j = j;
	while (cmd_node->cmd_tab[i][j] && cmd_node->cmd_tab[i][j] != 32
		&& cmd_node->cmd_tab[i][j] != 39 && cmd_node->cmd_tab[i][++j] != '$')
		size_dol++;
	diff = ft_strlen(cmd_node->cmd_tab[i]) - size_dol;
	if (!diff)
	{
		free(cmd_node->cmd_tab[i]);
		cmd_node->cmd_tab[i] = ft_strdup("");
		return (0);
	}
	new_s = malloc(sizeof(char) * diff + 1);
	if (!new_s)
		error_mallc(data);
	new_s = copy_without_dol(cmd_node, i, tmp_j, new_s);
	free(cmd_node->cmd_tab[i]);
	cmd_node->cmd_tab[i] = ft_substr(new_s, 0, diff);
	free(new_s);
	return (-1);
}

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
		&& node->cmd_tab[i][j] != 39 && node->cmd_tab[i][++j] != '$')
	{
		if (!node->cmd_tab[i][j])
		{
			s[k] = '\0';
			return (s);
		}
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

int	while_dol(t_main *data, t_cmd_parse *node, int i, int dol)
{
	int	len;
	int	j;

	len = 0;
	while (node->cmd_tab[i][dol] == '$')
	{
		dol++;
		if (node->cmd_tab[i][dol] == '\0')
			return (0);
		else if (node->cmd_tab[i][dol] != '$')
		{
			len = expanding_bis(data, node, i, dol - 1);
			break ;
		}
	}
	if (len == 0)
		return (0);
	j = (dol - 1) + len;
	return (j);
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
	while (s[i] && s[i] != 32 && s[i] != '$' && s[i] != '-'
		&& s[i] != ':' && s[i] != '.')
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
