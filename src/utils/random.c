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

void	print_no_command(t_main *data, char *s, int i)
{
	int		ok;
	char	*tmp;

	ok = 0;
	if (s == NULL)
	{
		ft_putendl_fd(": command not found", 2);
		return ;
	}
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

int	check_qt(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i + 1] == '\0' || s[i + 1] == 32)
		{
			if (s[i] == 39)
				return (1);
		}
		i++;
	}
	return (0);
}

char	*cpyy(t_cmd_parse *node, int sizetab, int ok, char *s)
{
	int	j;
	int	k;

	k = 0;
	while (ok <= sizetab)
	{
		j = 0;
		while (node->cmd_tab[ok][j])
			s[k++] = node->cmd_tab[ok][j++];
		ok++;
		s[k++] = ' ';
		if (!node->cmd_tab[ok])
		{
			s[k] = '\0';
			break ;
		}
	}
	return (s);
}

int	f_len(t_cmd_parse *node, int sizetab, int i)
{
	int	len;

	len = 0;
	while (i <= sizetab)
	{
		len += ft_strlen(node->cmd_tab[i]) + 1;
		i++;
		if (!node->cmd_tab[i])
			break ;
	}
	return (len);
}
