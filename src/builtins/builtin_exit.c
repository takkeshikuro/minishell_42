/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:40 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/30 02:04:42 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_exit(t_main *data, t_cmd_parse *cmd_parse)
{
	ft_putendl_fd("exit", 1);
	free_kill(data);
	exit (0);
}

//free stuff avant l.appel dans first_builtins() dans exec_built.c
