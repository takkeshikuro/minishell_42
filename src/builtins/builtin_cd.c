/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:38 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/18 05:22:57 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**for_tmptab(t_main *data, char	**tmptab, char *s_new, char *s_old)
{
	int	i;

	i = 0;
	while (data->env_bis[i])
	{
		if (!ft_strncmp(data->env_bis[i], "PWD", 3))
			tmptab[i] = ft_strdup(s_new);
		else if (!ft_strncmp(data->env_bis[i], "OLDPWD", 6))
			tmptab[i] = ft_strdup(s_old);
		else
			tmptab[i] = ft_strdup(data->env_bis[i]);
		i++;
	}
	tmptab[i] = 0;
	return (tmptab);
}

void	switch_path(t_main *data, char *s_old, char *s_new)
{
	int		i;
	char	**tmptab;

	i = 0;
	s_new = ft_strjoin("PWD=", s_new);
	while (data->env_bis[i])
		i++;
	tmptab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmptab)
		exit (1);
	tmptab = for_tmptab(data, tmptab, s_new, s_old);
	free_tab(data->env_bis);
	data->env_bis = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->env_bis)
		exit (1);
	i = 0;
	while (tmptab[i])
	{
		data->env_bis[i] = ft_strdup(tmptab[i]);
		i++;
	}
	data->env_bis[i] = 0;
	free_tab(tmptab);
	free(s_new);
}

char	*just_copy(t_main *data, char *s, int i)
{
	int		j;
	int		k;
	char	*ok;

	j = 4;
	k = 0;
	while (data->env_bis[i][j])
		s[k++] = data->env_bis[i][j++];
	s[k] = '\0';
	ok = ft_strjoin("OLDPWD=", s);
	free(s);
	return (ok);
}

void	change_env(t_main *data)
{
	char	s_new[4096];
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
	s_old = malloc(sizeof(char) * ft_strlen(data->env_bis[i]) + 1);
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
		// print not a directory si c un fichier mais jsp faire
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
