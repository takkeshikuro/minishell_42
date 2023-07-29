/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:40 by keshikuro         #+#    #+#             */
/*   Updated: 2023/07/29 05:09:42 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_exit(t_main *data, t_cmd_parse *cmd_parse)
{
	printf("quit minishell\n");
	free_kill(data);
	exit (0);
}

//free stuff avant l.appel dans first_builtins() dans exec_built.c

