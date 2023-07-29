/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:02:15 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/07/29 04:42:32 by tmorikaw         ###   ########.fr       */
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

int	syntax_err(t_main *data, char *s)
{
	ft_putstr_fd("bash : syntax error ", 1);
	ft_putendl_fd(s, 1);
	data->return_value = 2;
	return (1);
}
