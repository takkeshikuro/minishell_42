/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:43 by keshikuro         #+#    #+#             */
/*   Updated: 2023/07/29 05:07:29 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	add_total_stuff(t_main *data, char *s)
{
	char	*s_quoted;
	char	*s_check;
	int		i;

	i = 0;
	s_quoted = malloc(sizeof(char) * ft_strlen(s) + 3);
	if (!s_quoted)
		exit (1);
	i = cp_string_quoted(s, s_quoted);
	s_quoted[i] = '\0';
	s_check = cp_string_name(s);
	if (check_v_exist_bis(data, s_check) >= 0)
		rm_variable_bis(data, check_v_exist_bis(data, s_check));
	if (check_v_exist_exp(data, s_check) >= 0)
		rm_variable_exp(data, check_v_exist_exp(data, s_check));
	add_to_bis(data, s);
	add_v_to_envexp(data, s_quoted);
	free(s_quoted);
	free(s_check);
}

void	export_support(t_main *data, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			add_total_stuff(data, s);
			break ;
		}
		else if (s[i + 1] == '\0')
		{
			if ((check_v_exist_bis(data, s) >= 0))
				return ;
			else if (check_v_exist_exp(data, s) >= 0)
				return ;
			add_v_to_envexp(data, s);
		}
		i++;
	}
	return ;
}

int	built_export(t_main *data, t_cmd_parse *cmd_parse)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	if (!cmd_parse->cmd_tab[1] || cmd_parse->cmd_tab[1][0] == '\0')
		return (show_env_exp(data));
	while (cmd_parse->cmd_tab[i])
	{
		if (simple_check(cmd_parse->cmd_tab[i]))
			return (1);
		else
			export_support(data, cmd_parse->cmd_tab[i]);
		i++;
	}
	data->return_value = 0;
	return (1);
}
