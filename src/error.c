/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:02:15 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/25 05:12:35 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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