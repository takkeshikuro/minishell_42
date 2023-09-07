/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dol_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 04:44:26 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/28 13:55:40 by tmorikaw         ###   ########.fr       */
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
		else if (node->cmd_tab[i][j_dol + 1] == '$'
			|| node->cmd_tab[i][j_dol + 1] == '-'
			|| node->cmd_tab[i][j_dol + 1] == ':'
			|| node->cmd_tab[i][j_dol + 1] == '.')
		{
			j_dol += 1;
			break ;
		}
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

int	copy_past(t_cmd_parse *cmd_node, int i, int j_dol, char *str_replace)
{
	int		k;
	int		len;
	char	*tmp_str;
	char	*s_after;

	k = 0;
	s_after = check_char_after(cmd_node, i, j_dol);
	len = ft_strlen(str_replace);
	tmp_str = just_alloc(len, j_dol, s_after);
	if (tmp_str == NULL)
		return (-123);
	while (k < j_dol)
	{
		tmp_str[k] = cmd_node->cmd_tab[i][k];
		k++;
	}
	if (s_after)
		k = copy_bis(tmp_str, str_replace, k, 0);
	else
		k = copy_bis(tmp_str, str_replace, k, 1);
	if (s_after)
		copy_bis(tmp_str, s_after, k, 1);
	free(cmd_node->cmd_tab[i]);
	cmd_node->cmd_tab[i] = ft_strdup(tmp_str);
	return (copy_past_return(s_after, tmp_str));
}

char	*keep_good_str(char **env, int nb_env)
{
	int		i;
	int		start;
	int		size;
	char	*str_dol;

	i = 0;
	while (env[nb_env][i] && env[nb_env][i] != '=')
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

char	*go_itoa_replace(t_main *data, char *s)
{
	char	*ok;
	char	*tmp_rv;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	tmp_rv = ft_itoa(data->return_value);
	ok = malloc(sizeof(char) * ft_strlen(s) + 2);
	if (!ok)
		error_mallc(data);
	while (s[i] != '$')
	{
		ok[i] = s[i];
		i++;
	}
	k = i + 2;
	while (tmp_rv[j])
		ok[i++] = tmp_rv[j++];
	while (s[k])
		ok[i++] = s[k++];
	ok[i] = '\0';
	free(tmp_rv);
	return (ok);
}
