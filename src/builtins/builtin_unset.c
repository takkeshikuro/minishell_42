/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:46 by keshikuro         #+#    #+#             */
/*   Updated: 2023/09/03 04:11:49 by keshikuro        ###   ########.fr       */
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
			tmp_tab = crt_exp(data, data->env_exp, decla, len);
			copy_good_exp(data, tmp_tab);
			break ;
		}
		i++;
	}
	free(decla);
	return ;
}

int	unset_dig(t_main *data, char *s, int len)
{
	char	**tmp_tab;

	tmp_tab = crt_bis(data, data->env_bis, s, len);
	copy_good_bis(data, tmp_tab);
	data->return_value = 0;
	return (1);
}

int	built_unset(t_main *data, t_cmd_parse *cmd_parse)
{
	int		i;
	int		j;
	int		len;

	i = 1;
	if (cmd_parse->cmd_tab[i])
	{
		len = ft_strlen(cmd_parse->cmd_tab[i]);
		j = 0;
		while (data->env_bis[j])
		{
			if (!ft_strncmp(data->env_bis[j], cmd_parse->cmd_tab[i], len)
				&& data->env_bis[j][len] == '=')
			{
				unset_dig(data, cmd_parse->cmd_tab[i], len);
				break ;
			}
			j++;
		}
		same_for_env_exp(data, cmd_parse->cmd_tab[i], len);
		same_for_hidetab(data, cmd_parse->cmd_tab[i], len);
		i++;
	}
	data->return_value = 0;
	return (1);
}
