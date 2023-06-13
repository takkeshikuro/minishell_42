/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:37:57 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/13 03:01:44 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	rm_dollard(t_cmd_parse *cmd_node, int i, int j)
{
	int		size_dol;
	char	*new;
	int		diff;

	size_dol = 0;
	while (cmd_node->cmd_tab[i][j] != '$')
		j++;
	while (cmd_node->cmd_tab[i][j] && cmd_node->cmd_tab[i][j] != 32)
	{
		j++;
		size_dol++;
	}
	diff = ft_strlen(cmd_node->cmd_tab[i]) - size_dol;
	if (!diff)
	{
		cmd_node->cmd_tab[i][0] = '\0';
		return ;
	}
	new = malloc(sizeof(char) * diff + 1);
	if (!new)
		exit(1);
	new = copy_without_dol(cmd_node, i, new);
	cmd_node->cmd_tab[i] = ft_substr(new, 0, diff);
	free(new);
}

void	expand_dollard(t_main *data, t_cmd_parse *cmd_node, int nb_env)
{
	int		i;
	int		j;
	char	*str_replace;

	i = 0;
	while (cmd_node->cmd_tab[i])
	{
		j = 0;
		while (cmd_node->cmd_tab[i][j])
		{
			if (cmd_node->cmd_tab[i][j] == '$')
			{
				str_replace = keep_good_str(data->env_bis, nb_env);
				copy_past(cmd_node, i, j, str_replace);
			}
			j++;
		}
		i++;
	}
}

void	expanding_bis(t_main *data, t_cmd_parse *cmd_node, int i)
{
	int	nb_env;
	int	j;

	nb_env = check_env_variable(data, cmd_node->cmd_tab[i]);
	j = 0;
	if (nb_env >= 0)
		expand_dollard(data, cmd_node, nb_env);
	else
		rm_dollard(cmd_node, i, j);
}

void	expanding(t_main *data)
{
	t_cmd_parse	*cmd_node;
	int			i;
	int			j;

	cmd_node = data->cmd_parse;
	while (cmd_node)
	{
		i = 0;
		while (cmd_node->cmd_tab[i])
		{
			j = 0;
			while (cmd_node->cmd_tab[i][j])
			{
				if (cmd_node->cmd_tab[i][j] == '$')
					expanding_bis(data, cmd_node, i);
				j++;
			}
			i++;
		}
		cmd_node = cmd_node->next;
	}
}
