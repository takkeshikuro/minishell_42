/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:38 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/09 17:06:17 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	switch_path(t_main *data, char *s_old, char *s_new)
{
	int	i;

	i = 0;
	s_new = ft_strjoin("PWD=", s_new);
	s_old = ft_strjoin("OLDPWD=", s_old);
	while (data->env_bis[i])
	{
		if (!ft_strncmp(data->env_bis[i], "PWD", 3))
			break ;
		i++;
	}
	data->env_bis[i] = ft_strdup(s_new);
	i = 0;
	while (data->env_bis[i])
	{
		if (!ft_strncmp(data->env_bis[i], "OLDPWD", 6))
			break ;
		i++;
	}
	data->env_bis[i] = ft_strdup(s_old);
	free(s_new);
	free(s_old);
}

char	*just_copy(t_main *data, char *s, int i)
{
	int	j;
	int	k;

	j = 4;
	k = 0;
	while (data->env_bis[i][j])
	{
		s[++k] = data->env_bis[i][j];
		j++;
	}
	s[j] == '\0';
	return (s);
}

void	change_env(t_main *data)
{
	char	s_new[256];
	char	*s_old;
	int		i;

	i = 0;
	if (getcwd(s_new, sizeof(s_new)) == NULL)
		error("getcwd() failed");
	while (data->env_bis[i])
	{
		if (!ft_strncmp(data->env_bis[i], "PWD", 3))
			break ;
		i++;
	}
	s_old = malloc(sizeof(char) * ft_strlen(data->env_bis[i]) * 2);
	if (!s_old)
		exit(1);
	s_old = just_copy(data, s_old, i);
	switch_path(data, s_old, s_new);
	free(s_old);
}

void	get_home(t_main *data)
{
	char	*home_str;
	int		i;

	i = 0;
	while (ft_strncmp(data->env_bis[i], "HOME", 4))
		i++;
	home_str = ft_substr(data->env_bis[i], 5, ft_strlen(data->env_bis[i]) - 5);
	chdir(home_str);
	free(home_str);
	return ;
}

int	built_cd(t_main *data, t_cmd_parse *cmd_parse)
{
	int	ok;

	if (!cmd_parse->cmd_tab[1])
	{
		get_home(data);
		change_env(data);
		data->return_value = 0;
		return (1);
	}
	ok = chdir(cmd_parse->cmd_tab[1]);
	if (ok == -1)
	{
		printf("bash: cd: %s: No such file or directory\n",
			cmd_parse->cmd_tab[1]);
		data->return_value = 1;
		return (1);
	}
	else
		change_env(data);
	data->return_value = 0;
	return (1);
}
