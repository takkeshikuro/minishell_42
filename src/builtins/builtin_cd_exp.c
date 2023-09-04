/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 01:44:31 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/25 01:54:56 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**for_tmptab_exp(t_main *data, char	**tmptab, char *new, char *old)
{
	int	i;

	i = 0;
	while (data->env_exp[i])
	{
		if (!ft_strncmp(data->env_exp[i], "declare -x PWD", 14))
			tmptab[i] = ft_strdup(new);
		else if (!ft_strncmp(data->env_exp[i], "declare -x OLDPWD", 17))
			tmptab[i] = ft_strdup(old);
		else
			tmptab[i] = ft_strdup(data->env_exp[i]);
		i++;
	}
	tmptab[i] = 0;
	return (tmptab);
}

void	switch_path_exp(t_main *data, char *s_old, char *s_new)
{
	int		i;
	char	**tmptab;

	i = 0;
	while (data->env_exp[i])
		i++;
	tmptab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmptab)
		error_mallc(data);
	tmptab = for_tmptab_exp(data, tmptab, s_new, s_old);
	free_tab(data->env_exp);
	data->env_exp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->env_exp)
		error_mallc(data);
	i = 0;
	while (tmptab[i])
	{
		data->env_exp[i] = ft_strdup(tmptab[i]);
		i++;
	}
	data->env_exp[i] = 0;
	free_tab(tmptab);
}

void	change_envexp(t_main *data, char *s_new)
{
	int		i;
	char	*s_old;

	i = 0;
	while (data->env_exp[i])
	{
		if (!ft_strncmp(data->env_exp[i], "declare -x PWD", 14))
			break ;
		i++;
	}
	s_old = malloc(sizeof(char) * ft_strlen(data->env_exp[i]) + 1);
	if (!s_old)
		error_mallc(data);
	s_old = copy_declarex(data, s_old, i);
	s_new = add_quote(data, s_new);
	switch_path_exp(data, s_old, s_new);
	free(s_new);
	free(s_old);
}
