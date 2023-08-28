/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:48:00 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/28 13:53:38 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	rm_dollard(t_cmd_parse *cmd_node, int i, int j)
{
	int		size_dol;
	char	*new;
	int		diff;
	int		tmp_j;

	size_dol = 0;
	tmp_j = j;
	while (cmd_node->cmd_tab[i][j] && cmd_node->cmd_tab[i][j++] != 32)
		size_dol++;
	diff = ft_strlen(cmd_node->cmd_tab[i]) - size_dol;
	if (!diff)
	{
		free(cmd_node->cmd_tab[i]);
		cmd_node->cmd_tab[i] = ft_strdup("");
		return (0);
	}
	new = malloc(sizeof(char) * diff + 1);
	if (!new)
		exit(1);
	new = copy_without_dol(cmd_node, i, tmp_j, new);
	free(cmd_node->cmd_tab[i]);
	cmd_node->cmd_tab[i] = ft_substr(new, 0, diff);
	free(new);
	return (0);
}

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
}


int	return_value(t_main *data, t_cmd_parse *node, int i, int j_dol)
{
	char	*str_replace;

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
		else
			return (expand_dollard(data, node, i, j));
	}
	else if (nb_env == -1)
		return (rm_dollard(node, i, j));
	else if (nb_env == -2)
		return (1);
	else if (nb_env == -3)
		return (return_value(data, node, i, j));
}

void	expanding(t_main *data, t_cmd_parse *node, int i, int j)
{
	int			dol;
	int			len;

	while (node->cmd_tab[i][j])
	{
		if (node->cmd_tab[i][j] == '$')
		{
			dol = j;
			while (node->cmd_tab[i][dol] == '$')
				dol++;
			if (node->cmd_tab[i][dol] == '\0' || node->cmd_tab[i][dol] == 32)
				len = (dol - j);
			else
			{
				len = expanding_bis(data, node, i, j);
				break ;
			}
			j += len;
		}
		j++;
	}
	if (!node->cmd_tab[i][j])
		return ;
	expanding(data, node, i, 0);
}
