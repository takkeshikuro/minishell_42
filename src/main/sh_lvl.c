/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lvl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:17:20 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/09/09 09:19:29 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	change_sh_value(t_main *data, char *new_shlvl, char *old)
{
	int	i;

	i = 0;
	while (data->env_bis[i])
	{
		if (!ft_strncmp(data->env_bis[i], old, 5))
			break ;
		i++;
	}
	free(data->env_bis[i]);
	data->env_bis[i] = ft_strdup(new_shlvl);
}

char	*get_var_value(t_main *data, char *str)
{
	char	*ok;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str || !ft_strchr(str, '='))
		return (NULL);
	while (str[i] != '=')
		i++;
	i++;
	ok = malloc(ft_strlen(str) - i + 1);
	if (!ok)
		error_mallc(data);
	while (str[i + j])
	{
		ok[j] = str[i + j];
		j++;
	}
	ok[j] = '\0';
	return (ok);
}

char	*search_var(char **env, char *name)
{
	char	*dest;
	int		i;
	int		size;

	i = 0;
	size = ft_strlen(name);
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], size) && (env[i][size] == '='))
		{
			dest = env[i];
			return (dest);
		}
		i++;
	}
	return (NULL);
}

int	check_shlvl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

void	get_shlvl(t_main *data, char **env)
{
	int		shlvl;
	char	*value;
	char	*shell_lvl;
	char	*new_shlvl;

	shell_lvl = search_var(env, "SHLVL");
	if (!shell_lvl)
		return ;
	value = get_var_value(data, shell_lvl);
	if (!value || check_shlvl(value))
		return ;
	shlvl = ft_atoi(value) + 1;
	free(value);
	value = ft_itoa(shlvl);
	new_shlvl = ft_strjoin("SHLVL=", value);
	change_sh_value(data, new_shlvl, shell_lvl);
	free(value);
	free(new_shlvl);
}
