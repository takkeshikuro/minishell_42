/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dol_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 04:44:26 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/03 12:32:25 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	copy_past(t_cmd_parse *cmd_node, int i, int j, char *str_replace)
{
	int	k;
	int p;
	char *tmp_str;
	
	k = 0;
	tmp_str = (char *)malloc(sizeof(char) * (j + ft_strlen(str_replace)) + 1);
	if (!tmp_str)
		exit (1);
	while (cmd_node->cmd_tab[i][k] != '$')
	{
		tmp_str[k] = cmd_node->cmd_tab[i][k];
		k++;
	}
	p = 0;
	while (str_replace[p])
	{
		tmp_str[k] = str_replace[p];
		k++;
		p++;
	}
	tmp_str[k] = '\0';
	free(cmd_node->cmd_tab[i]);
	cmd_node->cmd_tab[i] = ft_strdup(tmp_str);

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
	while (s[i])
	{
		i++;
		size++;
	}
	str_dol = ft_substr(s, start_dol, size);
	result = check_env_bis(data->env_bis, str_dol);
	free(str_dol);
	return (result);
}
