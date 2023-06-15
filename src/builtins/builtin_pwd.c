/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 07:40:54 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/15 14:38:56 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_pwd(t_main *data, t_cmd_parse *cmd_parse)
{
	char	s[256];

	(void)data;
	(void)cmd_parse;
	//	if (chdir("/tmp") != 0)
	//		perror("chdir() error()");
	if (getcwd(s, sizeof(s)) == NULL)
		error("getcwd() failed");
	else
		printf("%s\n", s);
	data->return_value = 0;
	return (0);
}
