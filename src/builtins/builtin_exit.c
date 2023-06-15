/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:05:40 by keshikuro         #+#    #+#             */
/*   Updated: 2023/06/15 14:38:47 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_exit(t_main *data, t_cmd_parse *cmd_parse)
{
	printf("quit minishell\n");
	free_kill(data);
	exit(0);
}

// add 	data->return_value = ;

