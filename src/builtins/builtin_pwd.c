/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 07:40:54 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/22 01:41:32 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_pwd(t_main *data, t_cmd_parse *cmd_parse)
{
	char	*s;

	(void)data;
	(void)cmd_parse;
	//	if (chdir("/tmp") != 0)
	//		perror("chdir() error()");
	s = malloc(4096);
	if (!s)
		exit (1);
	if (getcwd(s, 4096) == NULL)
		error("getcwd() failed");
	else
		ft_putendl_fd(s, 1);
	free(s);
	data->return_value = 0;
	return (0);
}
