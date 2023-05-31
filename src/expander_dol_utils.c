/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 04:44:26 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/31 05:12:39 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	copy_past(t_cmd_parse *cmd_node, int i, int j, char *str_replace)
{
	int	k;

	k = 0;
	while (str_replace[k])
	{
		cmd_node->cmd_tab[i][j] = str_replace[k];
		k++;
		j++;
	}
	cmd_node->cmd_tab[i][j] = '\0';
}

char	*good_variable(char *s)
{
	int		i;
	int		tmp;
	char	*str;

	i = 0;
	while (s[i] != '=')
		i++;
	i += 1;
	tmp = i;
	i = 0;
	while (s[i])
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		exit(1);
	i = 0;
	while (s[tmp])
	{
		str[i] = s[tmp];
		i++;
		tmp++;
	}
	str[i] = '\0';
	return (str);
}

int	check_env_bis(char **env, char *str_dol)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str_dol, ft_strlen(str_dol)))
			return (1);
		i++;
	}
	return (0);
}

int	check_env_variable(t_main *data, char *s)
{
	char	*str_dol;
	int		i;
	int		start_dol;
	int		size;

	i = 0;
	size = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (s[i + 1] == '\0')
		return (1);
	start_dol = i;
	while (s[i])
	{
		i++;
		size++;
	}
	str_dol = ft_substr(s, start_dol, size);
	if (check_env_bis(data->env_ok, str_dol))
	{
		free(str_dol);
		return (1);
	}
	free(str_dol);
	return (0);
}
