/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:28:59 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/07/29 06:35:15 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	eot_handler(t_main *data)
{
	printf("Quit minishell by crtl-D\n");
	free_tab(data->env_bis);
	data->env_bis = NULL;
	free_tab(data->env_exp);
	data->env_exp = NULL;
	exit(0);
}

void	sig_handler(int sig)
{		
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
/* 		if (global_int[0] == 100)
			return ; */
		rl_redisplay();
	}
}

void	init_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
