/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:02:15 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/30 12:47:46 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error(t_main *data, char *s, int rv)
{
	ft_putendl_fd(s, 2);
	if (rv == 2)
		data->return_value = 2;
	else if (rv == 127)
		data->return_value = 127;
	else
		data->return_value = rv;
	return (1);
}

int	error_main(char *s)
{
	ft_putendl_fd(s, 1);
	return (1);
}

void	void_error(char *s)
{
	printf("error : %s\n", s);
	return ;
}

int	is_dir_error(t_main *data, char *s, int ok)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(s, 2);
	if (ok)
	{
		data->return_value = 127;
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		data->return_value = 126;
		ft_putstr_fd(": Is a directory\n", 2);
	}
	return (1);
}

int	syntax_err(t_main *data, char *s)
{
	ft_putstr_fd("bash : syntax error ", 1);
	ft_putendl_fd(s, 1);
	data->return_value = 2;
	return (1);
}
