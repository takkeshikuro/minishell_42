/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:02:15 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/23 06:03:30 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	error(char *s)
{
	printf("error : %s\n", s);
	exit(1);
}

void	void_error(char *s)
{
	printf("error : %s\n", s);
	return ;
}
