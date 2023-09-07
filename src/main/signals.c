/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:28:59 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/09/03 04:17:19 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	eot_handler(t_main *data)
{
	printf("Quit minishell by ctrl-D\n");
	free_kill(data);
	clear_history();
	exit(0);
}

void	sig_handler(int sig)
{
	int	*rv;

	rv = rv_adress(NULL);
	if (sig == SIGINT)
	{
		*rv = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
