/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_mana_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:30:04 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/30 03:12:32 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_set(char c, int quote)
{
	if (c == quote)
		return (1);
	return (0);
}

char	*ft_strim(t_main *data, char const *s1, int quote)
{
	char			*str;
	size_t			start;
	size_t			end;
	size_t			i;

	start = 0;
	while (s1[start] && check_set(s1[start], quote))
		start++;
	end = ft_strlen(s1);
	while (end > start && check_set(s1[end - 1], quote))
		end--;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		error_mallc(data);
	i = 0;
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*cpqt(t_main *data, char *s, int j, int qt)
{
	int		i;
	char	*ok;

	i = 0;
	ok = malloc(sizeof(char) * ft_strlen(s) - nb_qt(s, qt) + 1);
	if (!ok)
		error_mallc(data);
	while (s[i])
	{
		if (s[i] == qt)
			i++;
		else
			ok[j++] = s[i++];
		if (s[i] == '\0')
		{
			ok[j] = '\0';
			break ;
		}
	}
	return (ok);
}

char	*rm_qt_redir(t_main *data, char *s, int qt, int j)
{
	char	*new;

	if (nb_qt(s, qt))
	{
		if (nb_qt(s, qt) == 2)
			new = ft_strim(data, s, qt);
		else
			new = cpqt(data, s, j, qt);
		return (new);
	}
	else
		return (NULL);
}

void	check_qt_redir(t_main *data, t_lexer *node)
{
	t_lexer	*tmp;
	char	*s_trim;

	tmp = node;
	while (tmp)
	{
		if (tmp->str)
		{
			if (nb_qt(tmp->str, 39))
			{
				s_trim = rm_qt_redir(data, tmp->str, 39, 0);
				free(tmp->str);
				tmp->str = s_trim;
			}
			else if (nb_qt(tmp->str, 34))
			{
				s_trim = rm_qt_redir(data, tmp->str, 34, 0);
				free(tmp->str);
				tmp->str = s_trim;
			}
		}
		tmp = tmp->next;
	}
}
