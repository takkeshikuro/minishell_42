/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:38 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/30 12:47:20 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**for_tmptab(t_main *data, char	**tmptab, char *new, char *old)
{
	int	i;

	i = 0;
	while (data->env_bis[i])
	{
		if (!ft_strncmp(data->env_bis[i], "PWD", 3))
			tmptab[i] = ft_strdup(new);
		else if (!ft_strncmp(data->env_bis[i], "OLDPWD", 6))
			tmptab[i] = ft_strdup(old);
		else
			tmptab[i] = ft_strdup(data->env_bis[i]);
		i++;
	}
	tmptab[i] = 0;
	return (tmptab);
}

void	switch_path_bis(t_main *data, char *s_old, char *s_new)
{
	int		i;
	char	**tmptab;

	i = 0;
	s_new = ft_strjoin("PWD=", s_new);
	while (data->env_bis[i])
		i++;
	tmptab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmptab)
		error_mallc(data);
	tmptab = for_tmptab(data, tmptab, s_new, s_old);
	free_tab(data->env_bis);
	data->env_bis = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->env_bis)
		error_mallc(data);
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

void	change_envbis(t_main *data)
{
	char	s_new[4096];
	char	*s_old;
	int		i;

	i = 0;
	if (getcwd(s_new, sizeof(s_new)) == NULL)
	{
		error(data, "getcwd() failed", 1);
		return ;
	}
	while (data->env_bis[i])
	{
		if (!ft_strncmp(data->env_bis[i], "PWD", 3))
			break ;
		i++;
		if (!data->env_bis[i])
			return ;
	}
	s_old = malloc(sizeof(char) * ft_strlen(data->env_bis[i]) + 1);
	if (!s_old)
		error_mallc(data);
	s_old = just_copy(data, s_old, i);
	switch_path_bis(data, s_old, s_new);
	free(s_old);
	change_envexp(data, s_new);
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
		change_envbis(data);
		data->return_value = 0;
		return (1);
	}
	if (check_argg(data, cmd_parse->cmd_tab))
		return (1);
	ok = chdir(cmd_parse->cmd_tab[1]);
	if (ok == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(cmd_parse->cmd_tab[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		data->return_value = 1;
		return (1);
	}
	else
		change_envbis(data);
	data->return_value = 0;
	return (1);
}
