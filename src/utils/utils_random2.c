/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_random2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 08:56:06 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/09/01 20:05:31 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmpchar(char c, char ok)
{
	if (c == ok)
		return (1);
	return (0);
}

char	*just_alloc(int len, int j_dol, char *s_af)
{
	char	*ok;

	if (s_af)
		ok = malloc(sizeof(char) * (j_dol + len + ft_strlen(s_af)) + 1);
	else
		ok = malloc(sizeof(char) * (j_dol + len) + 1);
	if (!ok)
		return (NULL);
	return (ok);
}

void	built_move(t_cmd_parse *node, size_t ok)
{
	char	**tab;

	if (ft_strlen(node->cmd_tab[0]) == ok)
		return ;
	tab = ft_split(node->cmd_tab[0], ' ');
	free_tab(node->cmd_tab);
	node->cmd_tab = tab;
	return ;
}

int	built_found(char *s)
{
	if (!ft_strncmp(s, "echo", 4) || !ft_strncmp(s, "exit", 4))
		return (4);
	else if (!ft_strncmp(s, "export", 6))
		return (6);
	else if (!ft_strncmp(s, "cd", 2))
		return (2);
	else if (!ft_strncmp(s, "unset", 5))
		return (5);
	else
		return (0);
}

void	check_echo_tab(t_main *data)
{
	t_cmd_parse	*node;
	int			i;

	node = data->cmd_parse;
	i = 0;
	while (node)
	{
		i = 0;
		while (node->cmd_tab[i])
			i++;
		if (i == 1 && built_found(node->cmd_tab[0]))
			built_move(node, built_found(node->cmd_tab[0]));
		node = node->next;
	}
}
