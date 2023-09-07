/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:48:00 by keshikuro         #+#    #+#             */
/*   Updated: 2023/09/03 02:36:21 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expand_dollard(t_main *data, t_cmd_parse *node, int i, int j)
{
	int		nb_env;
	int		ok;
	char	*str_replace;

	nb_env = check_env_variable(data, node->cmd_tab[i], j);
	if (node->cmd_tab[i][j] == '$')
	{
		str_replace = keep_good_str(data->env_bis, nb_env);
		copy_past(node, i, j, str_replace);
		ok = ft_strlen(str_replace);
		free(str_replace);
		return (ok);
	}
	return (1);
}

int	return_value(t_main *data, t_cmd_parse *node, int i, int j_dol)
{
	char	*str_replace;

	(void)j_dol;
	if (ft_strlen(node->cmd_tab[i]) == 2)
		str_replace = ft_itoa(data->return_value);
	else
		str_replace = go_itoa_replace(data, node->cmd_tab[i]);
	free(node->cmd_tab[i]);
	node->cmd_tab[i] = ft_strdup(str_replace);
	free(str_replace);
	return (2);
}

int	expanding_bis(t_main *data, t_cmd_parse *node, int i, int j)
{
	int	nb_env;

	nb_env = check_env_variable(data, node->cmd_tab[i], j);
	if (nb_env >= 0)
	{
		if (nb_env == 999)
			return (expand_dol_qt(data, node, i, j));
		else if (nb_env == 888)
			return (expand_from_hidetab(data, node, i, j));
		else
			return (expand_dollard(data, node, i, j));
	}
	else if (nb_env == -1)
		return (rm_dollard(data, node, i, j));
	else if (nb_env == -2)
		return (1);
	else if (nb_env == -3)
		return (return_value(data, node, i, j));
	return (0);
}

int	second_expand(t_main *data, t_cmd_parse *node, int i, int j)
{
	if ((j < (int)ft_strlen(node->cmd_tab[i])) && node->cmd_tab[i][j])
	{
		while (node->cmd_tab[i][j])
		{
			if (node->cmd_tab[i][j] == '$')
			{
				while (node->cmd_tab[i][j] == '$')
					j++;
				if (!node->cmd_tab[i][j])
					break ;
				expanding(data, node, i, j - 1);
			}
			j++;
			if ((int)ft_strlen(node->cmd_tab[i]) < j)
				return (0);
		}
	}
	if (j > (int)ft_strlen(node->cmd_tab[i]))
		return (0);
	if (!node->cmd_tab[i][j])
		return (0);
	return (1);
}

void	expanding(t_main *data, t_cmd_parse *node, int i, int j)
{
	int			dol;

	while ((j < (int)ft_strlen(node->cmd_tab[i])) && node->cmd_tab[i][j])
	{
		if (node->cmd_tab[i][j] == '$')
		{
			if (!node->cmd_tab[i][j + 1])
				return ;
			dol = j;
			j = while_dol(data, node, i, dol);
			if (!j)
				return ;
			if (!second_expand(data, node, i, j))
				return ;
		}
		j++;
	}
}
