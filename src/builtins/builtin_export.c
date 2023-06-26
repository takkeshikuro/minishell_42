/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:43 by keshikuro         #+#    #+#             */
/*   Updated: 2023/06/26 03:47:45 by keshikuro        ###   ########.fr       */
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
	char	*tmp_s;
	char	*check_tmp;
	int		i;

	i = 0;
	tmp_s = malloc(sizeof(char) * ft_strlen(s) + 3);
	if (!tmp_s)
		exit (1);
	i = cp_string(s, tmp_s);
	tmp_s[i] = '\0';
	check_tmp = good_tmp(s);
//	if (check_v_exist_bis(data, check_tmp) >= 0)
//		rm_variable_bis(data, check_v_exist_bis(data, check_tmp));
//	if (check_v_exist_exp(data, check_tmp) >= 0)
//		rm_variable_exp(data, check_v_exist_exp(data, check_tmp));
	add_to_bis(data, s);
	add_v_to_envexp(data, tmp_s);
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
			{
				fprintf(stderr, "return\n");
				return ;
			}
			add_v_to_envexp(data, s);
		//	show_env_exp(data);
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
	fprintf(stderr, "no more in builtin\n");
}
