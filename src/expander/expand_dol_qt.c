/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dol_qt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:56:49 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/30 03:10:33 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

char	*add_qt(char *s)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	new = malloc(sizeof(char) * i + 2);
	if (!new)
		exit (1);
	i = 0;
	while (s[i])
		new[j++] = s[i++];
	new[j++] = '\'';
	new[j] = '\0';
	return (new);
}

char	*keep_good_str_qt(char **env, int nb_env)
{
	int		i;
	int		start;
	int		size;
	char	*str_dol;

	i = 0;
	while (env[nb_env][i] != '=')
		i++;
	i += 1;
	start = i;
	size = i;
	while (env[nb_env][i])
	{
		size++;
		i++;
	}
	str_dol = ft_substr(env[nb_env], start, size);
	if (!str_dol)
		exit(1);
	return (str_dol);
}

int	check_env_bis_qt(char **env, char *str_dol)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str_dol);
	while (env[i])
	{
		if (!ft_strncmp(env[i], str_dol, len - 1) && env[i][len - 1] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	check_env_variable_qt(t_main *data, char *s, int j)
{
	char	*str_dol;
	int		i;
	int		size;
	int		result;

	size = 0;
	i = j + 1;
	while (s[i] && s[i] != 32)
	{
		i++;
		size++;
	}
	str_dol = ft_substr(s, j + 1, (size - 1));
	result = check_env_bis_qt(data->env_bis, str_dol);
	free(str_dol);
	return (result);
}

int	expand_dol_qt(t_main *data, t_cmd_parse *node, int i, int j)
{
	int		nb_env;
	int		ok;
	char	*str_replace;
	char	*final;

	nb_env = check_env_variable_qt(data, node->cmd_tab[i], j);
	if (node->cmd_tab[i][j] == '$')
	{
		str_replace = keep_good_str_qt(data->env_bis, nb_env);
		final = add_qt(str_replace);
		copy_past(node, i, j, final);
		ok = ft_strlen(str_replace);
		free(str_replace);
		free(final);
		return (ok);
	}
	return (1);
}
