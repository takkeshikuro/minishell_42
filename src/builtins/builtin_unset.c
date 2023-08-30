/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:46 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/30 01:24:07 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	same_for_env_exp(t_main *data, char *s, int len)
{
	int		i;
	char	**tmp_tab;
	char	*decla;

	decla = ft_strjoin("declare -x ", s);
	i = 0;
	while (data->env_exp[i])
	{
		if (!ft_strncmp(data->env_exp[i], decla, len + 11)
			&& data->env_exp[i][11 + len] == '=')
		{
			tmp_tab = crt_exp(data->env_exp, decla, len);
			copy_good_exp(data, tmp_tab);
			break ;
		}
		i++;
	}
	free(decla);
	return ;
}

int	built_unset(t_main *data, t_cmd_parse *cmd_parse)
{
	int		i;
	int		j;
	int		len;
	char	**tmp_tab;

	i = 1;
	while (cmd_parse->cmd_tab[i])
	{
		len = ft_strlen(cmd_parse->cmd_tab[i]);
		j = 0;
		while (data->env_bis[j])
		{
			if (!ft_strncmp(data->env_bis[j], cmd_parse->cmd_tab[i], len)
				&& data->env_bis[j][len] == '=')
			{
				tmp_tab = crt_bis(data->env_bis, cmd_parse->cmd_tab[i], len);
				copy_good_bis(data, tmp_tab);
				break ;
			}
			j++;
		}
		same_for_env_exp(data, cmd_parse->cmd_tab[i++], len);
	}
	data->return_value = 0;
	return (1);
}
