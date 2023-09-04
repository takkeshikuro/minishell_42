/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:02:15 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/09/04 15:20:42 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_argg(t_main *data, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("bash: cd: too many arguments", 2);
		data->return_value = 1;
		return (1);
	}
	return (0);
}

int	ft_perror(char *s)
{
	(void)s;
	ft_putendl_fd(" Is a directory", 2);
	return (1);
}

void	error_mallc(t_main *data)
{
	free_kill(data);
	reset_stuff(data);
	exit (1);
}
