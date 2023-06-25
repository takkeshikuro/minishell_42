/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:43 by keshikuro         #+#    #+#             */
/*   Updated: 2023/06/25 02:56:26 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	equal_env(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i + 1);
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

int	check_variable(t_main *data, char *s)
{
	int i;

	i = 0;
	while (data->env_bis[i])
	{
		if (!ft_strncmp(data->env_bis[i], s, equal_env(data->env_bis[i])))
		{
			free(data->env_bis[i]);
			data->env_bis[i] = ft_strdup(s);
			return (1);
		}
		i++;
	}
}

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

int	simple_check(char *s)
{
	int		i;

	i = 0;
	while (s[i] == 32)
		i++;
	if (s[i] == '\0')
		return (print_error_export(s, 1));
	if (ft_isdigit(s[0]) || check_valid_identifier(s[0]))
		return (print_error_export(s, 1));
	i = 0;
	while (s[i] != '=')
	{
		if (s[i] == '\0')
			break ;
		if (check_valid_identifier(s[i]))
			return (print_error_export(s, 1));
		i++;
	}
	return (0);
}

int	built_export(t_main *data, t_cmd_parse *cmd_parse)
{
    int i;
	char *tmp;

	i = 0;
	if (!cmd_parse->cmd_tab[1] || cmd_parse->cmd_tab[1][0] == '\0')
		return (show_env_exp(data));
	if (simple_check(cmd_parse->cmd_tab[1]))
		return (1);
	while (cmd_parse->cmd_tab[1][i])
	{
		if (cmd_parse->cmd_tab[1][i] == '=')
			//function do shit
		i++;
	}
	//function add varibale to env export;
}
