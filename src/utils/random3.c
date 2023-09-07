/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 05:36:36 by keshikuro         #+#    #+#             */
/*   Updated: 2023/09/07 06:23:09 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	var_found(t_main *data, char *s, int len)
{
	int	i;

	i = 0;
	while (data->env_bis[i])
	{
		if (!ft_strncmp(s + 1, data->env_bis[i], len - 1)
			&& data->env_bis[i][len - 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	file_check(t_main *data, char *s)
{
	int	i;

	i = 0;
	if (s[i] == '.' && s[i + 1] == '/')
	{
		if (opendir(s + 2))
		{
			data->return_value = 126;
			return (ft_perror(s));
		}
		else if (access(s + 2, F_OK))
		{
			data->return_value = 127;
			perror(s);
			return (1);
		}
		data->return_value = 0;
	}
	return (0);
}

int	var_check(t_main *data, t_lexer *lst)
{
	int	len;

	if (lexer_size(lst) == 1)
	{
		if (lst->str)
		{
			len = ft_strlen(lst->str);
			if (lst->str[0] == '$')
			{
				if (len == 1)
					return (error(data, "$: command not found", 127));
				if (!ft_strncmp(lst->str + 1, "?", 1) && len == 2)
					return (0);
				if (!ft_strncmp(lst->str + 1, "PWD", 3) && len == 4)
					return (is_dir_error(data, "$PWD", 0));
				if (!ft_strncmp(lst->str + 1, "OLDPWD", 3) && len == 7)
					return (is_dir_error(data, "$OLDPWD", 0));
				else if (!var_found(data, lst->str, len))
					return (1);
			}
			return (file_check(data, lst->str));
		}
	}
	return (0);
}

int	add_w_dig(char *str, int i, int j)
{
	while (str[i + j] && !is_operateur(str[i + j]))
	{
		if (str[i + j] == 34)
		{
			j++;
			while (str[i + j] != 34 && str[i + j])
				j++;
			j++;
			break ;
		}
		else if (str[i + j] == 39)
		{
			j++;
			while (str[i + j] != 39 && str[i + j])
				j++;
			j++;
			break ;
		}
		else
			j++;
	}
	return (j);
}

int	copy_past_return(char *s_after, char *tmp_str)
{
	free(s_after);
	free(tmp_str);
	return (0);
}
