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
	int		i;

	i = 0;
	if (ft_strlen(node->cmd_tab[0]) == ok)
		return ;
	if (!node->cmd_tab[0][0])
		return ;
	while (node->cmd_tab[0][i] == ' ')
	{
		i++;
		if (!node->cmd_tab[0][i])
			return ;
	}
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
		return (-10);
}

void	brand_new_tab(t_main *data, t_cmd_parse *node, int i, int len)
{
	char	*s;
	char	**tab;
	int		ok;
	int		sizetab;

	sizetab = sizeof(node->cmd_tab);
	while (++i <= sizetab)
	{
		if (node->cmd_tab[i][0])
		{
			ok = i;
			len = f_len(node, sizetab, i);
			break ;
		}
	}
	s = malloc(sizeof(char) * len + 1);
	if (!s)
		error_mallc(data);
	cpyy(node, sizetab, ok, s);
	tab = ft_split(s, ' ');
	free(s);
	free_tab(node->cmd_tab);
	node->cmd_tab = tab;
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
		if (!node->cmd_tab[0])
			return ;
		while (node->cmd_tab[i])
			i++;
		if (node->d_qt == 2 || node->s_qt == 2)
		{
			if (check_qt_tab(node, 0, 0))
				return ;
		}
		if (i == 1 && built_found(node->cmd_tab[0]))
			built_move(node, built_found(node->cmd_tab[0]));
		else if (empty_case(node->cmd_tab))
			brand_new_tab(data, node, -1, 0);
		node = node->next;
	}
}
