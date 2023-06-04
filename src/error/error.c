/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:02:15 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/04 16:04:13 by keshikuro        ###   ########.fr       */
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

void	exit_bash_error(char *s)
{
	printf("bash : %s", s);
	exit (1);
}
