/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 05:36:36 by keshikuro         #+#    #+#             */
/*   Updated: 2023/09/03 00:42:22 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_no_command(t_main *data, char *s)
{
	int		i;
	int		ok;
	char	*tmp;

	i = 0;
	ok = 0;
	while (data->env_bis[i])
	{
		if (!ft_strncmp(data->env_bis[i++], "PATH=", 5))
			ok = 1;
	}
	if (ok)
	{
		write(2, s, ft_strlen(s));
		ft_putendl_fd(": command not found", 2);
		return ;
	}
	tmp = ft_strjoin(s, ": No such file or directory\n");
	write(2, tmp, ft_strlen(tmp));
	free(tmp);
	return ;
}

void	print_intro(void)
{
	ft_putendl_fd("Welcome to", 1);
	ft_putendl_fd("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     \
██╗     ", 1);
	ft_putendl_fd("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     \
██║     ", 1);
	ft_putendl_fd("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     \
██║     ", 1);
	ft_putendl_fd("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     \
██║     ", 1);
	ft_putendl_fd("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗\
███████╗", 1);
	ft_putendl_fd("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝\
╚══════╝", 1);
	ft_putendl_fd("Copyright (C) 2023 | Made in 42 Paris, by Rayan Minh Marécar\
 and Théo Takeshi Morikawa.", 1);
	ft_putendl_fd("", 1);
}
