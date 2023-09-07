/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:29:32 by keshikuro         #+#    #+#             */
/*   Updated: 2023/09/03 01:52:06 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	*rv_adress(int *rv)
{
	static int	*rv_adress;

	if (rv)
		rv_adress = rv;
	return (rv_adress);
}

void	init_stuff(t_main *data)
{
	data->lexer_list = NULL;
	data->cmd_parse = NULL;
	data->hidetab = NULL;
	data->return_value = 0;
	data->syntaxe_check = 0;
	rv_adress(&(data->return_value));
	init_signals();
}

void	reset_stuff(t_main *data)
{
	if (data->input_line)
		free(data->input_line);
	if (data->lexer_list)
		free_lxr_lst(data->lexer_list);
	data->lexer_list = NULL;
	if (data->syntaxe_check == 0)
	{
		if (data->cmd_parse)
			free_cmd_tab(data);
		if (data->cmd_parse)
			free_cmd_lst(data->cmd_parse);
	}
	data->syntaxe_check = 0;
	data->cmd_parse = NULL;
	init_signals();
}

void	pr(t_lexer *lexer_list)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
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
			fprintf(stderr, "(%s)]", tmp->str);
		else
			fprintf(stderr, "%d]", tmp->i);
		i++;
		tmp = tmp->next;
	}
	fprintf(stderr, "\n");
}

void	pr_redir(t_lexer *lexer_list)
{
	t_lexer		*tmp;
	int			i;

	i = 0;
	fprintf(stderr, "[CHECK REDIR]");
	if (!lexer_list)
	{
		fprintf(stderr, "no redir list\n");
		return ;
	}
	tmp = lexer_list;
	while (tmp)
	{
		fprintf(stderr, " | node %d: ", i);
		if (tmp->str)
			fprintf(stderr, "file=[%s] ", tmp->str);
		if (tmp->operateur)
		tmp = tmp->next;
		i++;
	}
	fprintf(stderr, "\n");
}

void	prrr(t_cmd_parse *cmd_parse, int ok)
{
	t_cmd_parse	*tmp;
	int			i;

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
