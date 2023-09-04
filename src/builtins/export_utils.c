/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:39:30 by keshikuro         #+#    #+#             */
/*   Updated: 2023/06/26 16:05:21 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_error_export(char *s, int ok)
{
	int	i;

	i = 0;
	if (ok)
	{
		ft_putstr_fd("minishell: export: `", 2);
		while (s[i] && s[i] != '=')
			ft_putchar_fd(s[i++], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

int	equal_env(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	check_valid_identifier(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~'
		|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*')
	{
		return (1);
	}
	else
		return (0);
}

char	*cp_string_name(t_main *data, char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s[i] != '=')
		i++;
	tmp = malloc(sizeof(char) * i + 1);
	if (!tmp)
		error_mallc(data);
	i = 0;
	while (s[i] != '=')
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	cp_string_quoted(char *s1, char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != '=')
	{
		s2[i] = s1[i];
		i++;
		j++;
	}
	s2[j++] = '=';
	s2[j++] = '"';
	i++;
	while (s1[i])
	{
		s2[j] = s1[i];
		i++;
		j++;
	}
	s2[j++] = '"';
	return (j);
}
