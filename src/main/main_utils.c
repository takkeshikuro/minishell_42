/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:29:32 by keshikuro         #+#    #+#             */
/*   Updated: 2023/06/04 16:30:37 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pr(t_lexer *lexer_list)			// for lexer
{
	t_lexer * tmp;
	int i = 0;

	fprintf(stderr, "[CHECK LEXER] ");
	if (!lexer_list)
	{
		fprintf(stderr, "lexer_list is clean\n");
		return ;
	}
	tmp = lexer_list;
	while (tmp)
	{
		fprintf(stderr, "[node %d: ", i);
		if (tmp->str)
			fprintf(stderr, "%s]", tmp->str);
		else
			fprintf(stderr, "%d]", tmp->i);
		i++;
		tmp = tmp->next;
	}
	fprintf(stderr, "\n");
}


void prrr(t_cmd_parse *cmd_parse, int ok)			//for parser
{
	t_cmd_parse *tmp;
	int i;

	tmp = cmd_parse;
	fprintf(stderr, "[FINAL LIST]");
	if (ok == 1)
		fprintf(stderr, " before expander :");
	else
		fprintf(stderr, " after expander :");
	while (tmp)
	{
		i = 0;
		fprintf(stderr, " | new node->cmd_tab = ");
		while (tmp->cmd_tab[i])
		{
			fprintf(stderr, "[%s]", tmp->cmd_tab[i]);
			i++;
		}
		tmp = tmp->next;
	}
	fprintf(stderr, "\n");
}

void	get_env(t_main *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env_bis = malloc(sizeof(char *) * i);
	if (!data->env_bis)
		exit (1);
	i = 0;
	while (env[i])
	{
		data->env_bis[i] = ft_strdup(env[i]);
		i++;
	}
	data->env_bis[i] = 0;
}