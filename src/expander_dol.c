/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:37:57 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/03 12:32:09 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	rm_dollard(t_main *data, t_cmd_parse *cmd_node)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_node->cmd_tab[i])
	{
		j = 0;
		while (cmd_node->cmd_tab[i][j])
		{
			if (cmd_node->cmd_tab[i][j] == '$' && j == 0)
				cmd_node->cmd_tab[i][j] = '\0';
			else if (cmd_node->cmd_tab[i][j] == '$' && j > 0)
				cmd_node->cmd_tab[i] = ft_substr(cmd_node->cmd_tab[i], 0, j);
			j++;
		}
		i++;
	}
}

char	*keep_good_str(char **env, int nb_env)
{
	int		i;
	int		start;
	int		size;
	char	*str_dol;

	i = 0;
	while (env[nb_env][i] != '=')
		i++;
	i += 1;
	start = i;
	size = i;
	while (env[nb_env][i])
	{
		size++;
		i++;
	}
	str_dol = ft_substr(env[nb_env], start, size);
	if (!str_dol)
		exit (1);
	return (str_dol);
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

/// a voir pour opti, la c complique frr, pb apres expand_dollard()
void	expanding_bis(t_main *data, t_cmd_parse *cmd_node, int i)
{
	int nb_env;

	nb_env = check_env_variable(data, cmd_node->cmd_tab[i]);
	if (nb_env >= 0)
		expand_dollard(data, cmd_node, nb_env);
	else
		rm_dollard(data, cmd_node);
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
