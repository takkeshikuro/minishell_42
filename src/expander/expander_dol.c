/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:48:00 by keshikuro         #+#    #+#             */
/*   Updated: 2023/06/22 23:59:33 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	rm_dollard(t_cmd_parse *cmd_node, int i, int j)
{
	int		size_dol;
	char	*new;
	int		diff;
	int 	tmp_j;

	size_dol = 0;
	tmp_j = j;
	while (cmd_node->cmd_tab[i][j] && cmd_node->cmd_tab[i][j] != 32)
	{
		j++;
		size_dol++;
	}
	diff = ft_strlen(cmd_node->cmd_tab[i]) - size_dol;
	if (!diff)
	{
		cmd_node->cmd_tab[i][0] = '\0';
		return (0);
	}
	new = malloc(sizeof(char) * diff + 1);
	if (!new)
		exit(1);
	new = copy_without_dol(cmd_node, i, tmp_j, new);
	cmd_node->cmd_tab[i] = ft_substr(new, 0, diff);
	free(new);
	return (0);
}

int		expand_dollard(t_main *data, t_cmd_parse *node, int i, int j)
{
	int		nb_env;
	char	*str_replace;

	nb_env = check_env_variable(data, node->cmd_tab[i], j);
	if (node->cmd_tab[i][j] == '$')
	{
		str_replace = keep_good_str(data->env_bis, nb_env);
		copy_past(node, i, j, str_replace);
		return (ft_strlen(str_replace));
	}
}

int	return_value(t_main *data, t_cmd_parse *node, int i, int j_dol)
{
	char *str_replace;
	
	str_replace = ft_itoa(data->return_value);
	copy_past(node, i, j_dol, str_replace);
	return (ft_strlen(str_replace));
}

int	expanding_bis(t_main *data, t_cmd_parse *node, int i, int j)
{
	int	nb_env;

	nb_env = check_env_variable(data, node->cmd_tab[i], j);
//	fprintf(stderr, "value exp bis = %d\n", nb_env);
	if (nb_env >= 0)
		return (expand_dollard(data, node, i, j));
	else if (nb_env == -1)
		return (rm_dollard(node, i, j));
	else if (nb_env == -2)
		return (1);
	else if (nb_env == -3)
		return (return_value(data, node, i, j));
}

void	expanding(t_main *data, t_cmd_parse *node, int i)
{
	int			j;
	int			len;

	j = 0;
	while (node->cmd_tab[i][j])
	{
		if (node->cmd_tab[i][j] == '$')
		{
			len = expanding_bis(data, node, i, j);
			j += len;
		}
		else
			j++;
	}
}
