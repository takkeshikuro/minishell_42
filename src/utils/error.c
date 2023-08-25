/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:02:15 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/08 15:49:44 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error(char *s)
{
	printf("error : %s\n", s);
	return (1);
}

void	void_error(char *s)
{
	printf("error : %s\n", s);
	return ;
}

int	is_dir_error(t_main *data, char *s, int ok)
{
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(s, 1);
	if (ok)
	{
		data->return_value = 127;
		ft_putstr_fd(": No such file or directory\n", 1);
	}
	else
	{
		data->return_value = 126;
		ft_putstr_fd(": Is a directory\n", 1);
	}
	free(s);
	return (1);
}

int	syntax_err(t_main *data, char *s)
{
	ft_putstr_fd("bash : syntax error ", 1);
	ft_putendl_fd(s, 1);
	data->return_value = 2;
	return (1);
}