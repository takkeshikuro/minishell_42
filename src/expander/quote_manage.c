/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 06:31:03 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/30 03:13:04 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*need_malloc(t_cmd_parse *node, int i)
{
	int		size;
	char	*str;

	size = ft_strlen(node->cmd_tab[i]);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		exit (1);
	return (str);
}

int	nb_qt(char *s, int quote)
{
	int		i;
	int		ok;

	i = 0;
	ok = 0;
	while (s[i])
	{
		if (s[i] == quote)
			ok++;
		i++;
	}
	return (ok);
}

char	*check_4_strim(t_cmd_parse *node, int i_tab, int qt)
{
	char	*new;

	if (node->cmd_tab[i_tab][0] == qt && nb_qt(node->cmd_tab[i_tab], qt) == 2)
	{
		new = ft_strim(node->cmd_tab[i_tab], qt);
		free(node->cmd_tab[i_tab]);
		node->cmd_tab[i_tab] = ft_strdup(new);
		return (new);
	}
	else
		return (NULL);
}

int	rm_quote(t_cmd_parse *node, int i_tab, int qt)
{
	char	*new;
	int		j;
	int		i;

	j = 0;
	i = 0;
	new = check_4_strim(node, i_tab, qt);
	if (!new)
	{
		new = need_malloc(node, i_tab);
		while (node->cmd_tab[i_tab][j])
		{
			if (node->cmd_tab[i_tab][j] == qt)
				j++;
			else
				new[i++] = node->cmd_tab[i_tab][j++];
		}
		new[i] = '\0';
		free(node->cmd_tab[i_tab]);
		node->cmd_tab[i_tab] = ft_strdup(new);
	}
	free(new);
	if (qt == 39)
		return (1);
	return (0);
}

int	quote_manage(t_main *data, t_cmd_parse *node, int i)
{
	int			j;

	j = 0;
	(void)data;
	while (node->cmd_tab[i][j])
	{
		if (node->cmd_tab[i][j] == 39)
			return (rm_quote(node, i, 39));
		else if (node->cmd_tab[i][j] == 34)
			return (rm_quote(node, i, 34));
		j++;
	}
	return (0);
}
