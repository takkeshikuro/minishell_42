/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 01:45:31 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/25 01:56:06 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*just_copy(t_main *data, char *s, int i)
{
	int		j;
	int		k;
	char	*ok;

	j = 4;
	k = 0;
	while (data->env_bis[i][j])
		s[k++] = data->env_bis[i][j++];
	s[k] = '\0';
	ok = ft_strjoin("OLDPWD=", s);
	free(s);
	return (ok);
}

char	*copy_declarex(t_main *data, char *s, int i)
{
	int		j;
	int		k;
	char	*ok;

	j = 15;
	k = 0;
	while (data->env_exp[i][j])
		s[k++] = data->env_exp[i][j++];
	s[k] = '\0';
	ok = ft_strjoin("declare -x OLDPWD=", s);
	free(s);
	return (ok);
}

char	*add_quote(t_main *data, char *s)
{
	int		i;
	int		j;
	char	*tmp;
	char	*ok;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!tmp)
		error_mallc(data);
	while (s[i])
		tmp[j++] = s[i++];
	tmp[j] = '\0';
	i = 0;
	j = 1;
	s[0] = '\"';
	while (tmp[i])
		s[j++] = tmp[i++];
	s[j++] = '\"';
	s[j] = '\0';
	ok = ft_strjoin("declare -x PWD=", s);
	free(tmp);
	return (ok);
}
