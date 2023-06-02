/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:37:57 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/02 23:54:47 by keshikuro        ###   ########.fr       */
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

char	*go_find(char **env, char *s)
{
	int		i;
	int		start_dol;
	int		size;
	char	*str_dol;

	i = 0;
	while (s[i] != '$')
		i++;
	start_dol = i;
	while (s[i])
	{
		i++;
		size++;
	}
	str_dol = ft_substr(s, start_dol, size);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str_dol, ft_strlen(str_dol)))
			return (good_variable(env[i]));
		i++;
	}
}

void	expand_dollard(t_main *data, t_cmd_parse *cmd_node)
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
				if (cmd_node->cmd_tab[i][j + 1] == '\0')
					return ;
				else
				{
					str_replace = go_find(data->env_ok, cmd_node->cmd_tab[i]);
					copy_past(cmd_node, i, j, str_replace);
				}
			}
			j++;
		}
		i++;
	}
}

/// a voir pour opti, la c complique frr, pb apres expand_dollard()
void	expanding_bis(t_main *data, t_cmd_parse *cmd_node, int i)
{
	
	if (check_env_variable(data, cmd_node->cmd_tab[i]))
	{
		fprintf(stderr, "go into expand dollard\n");
		expand_dollard(data, cmd_node);
	}
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
