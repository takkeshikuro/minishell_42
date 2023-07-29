/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dol_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 04:44:26 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/07/29 00:21:22 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*check_char_after(t_cmd_parse *node, int i, int j_dol)
{
	int		start;
	char	*tmp_str;

	while (node->cmd_tab[i][j_dol] != ' ')
	{
		if (node->cmd_tab[i][j_dol + 1] == '\0')
			return (NULL);
		j_dol++;
	}
	start = j_dol;
	while (node->cmd_tab[i][j_dol])
		j_dol++;
	tmp_str = ft_substr(node->cmd_tab[i], start, (j_dol - start));
	return (tmp_str);
}

int	copy_bis(char *s1, char *s2, int i, int ok)
{
	int	j;

	j = 0;
	while (s2[j])
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	if (ok)
		s1[i] = '\0';
	return (i);
}

void	copy_past(t_cmd_parse *cmd_node, int i, int j_dol, char *str_replace)
{
	int		k;
	int		len;
	char	*tmp_str;
	char	*str_after;

	k = 0;
	str_after = check_char_after(cmd_node, i, j_dol);
	len = ft_strlen(str_replace);
	if (str_after)
		tmp_str = malloc(sizeof(char) * (j_dol + len + ft_strlen(str_after)) + 1);
	else
		tmp_str = malloc(sizeof(char) * (j_dol + len) + 1);
	if (!tmp_str)
		exit(1);
	while (k < j_dol)
	{
		tmp_str[k] = cmd_node->cmd_tab[i][k];
		k++;
	}
	if (str_after)
		k = copy_bis(tmp_str, str_replace, k, 0);
	else
		k = copy_bis(tmp_str, str_replace, k, 1);
	if (str_after)
		copy_bis(tmp_str, str_after, k, 1);
	free(cmd_node->cmd_tab[i]);
	cmd_node->cmd_tab[i] = ft_strdup(tmp_str);
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
		exit(1);
	return (str_dol);
}
