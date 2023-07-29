/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:29:32 by keshikuro         #+#    #+#             */
/*   Updated: 2023/07/29 04:39:52 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_stuff(t_main *data)
{
	data->lexer_list = NULL;
	data->cmd_parse = NULL;
	data->return_value = 0;
	data->syntaxe_check = 0;
	init_signals();
}

void	free_cmd_tab(t_main *data)
{
	t_cmd_parse	*tmp;

	tmp = data->cmd_parse;
	while (tmp)
	{
		free_tab(tmp->cmd_tab);
		tmp->cmd_tab = NULL;
		tmp = tmp->next;
	}
}

void	free_cmd_lst(t_cmd_parse *lst)
{
	t_cmd_parse	*tmp;

	tmp = lst;
	while (tmp)
	{
		lst = tmp->next;
		if (tmp)
			free(tmp);
		tmp = lst;
	}
	free(lst);
}
void	free_lxr_lst(t_lexer *lst)
{
	t_lexer	*tmp;

	tmp = lst;
	while (tmp)
	{
		lst = tmp->next;
		if (tmp)
			free(tmp);
		tmp = lst;
	}
	free(lst);
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
		if (data->cmd_parse->cmd_tab[0])
			free_cmd_tab(data);
		if (data->cmd_parse)
			free_cmd_lst(data->cmd_parse);
		data->cmd_parse = NULL;
	}
	init_signals();
}

void	pr(t_lexer *lexer_list)			// show lexer list
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

void	pr_redir(t_lexer *lexer_list) // show redirection list
{
	t_lexer * tmp;
	int i = 0;

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
			fprintf(stderr, "redir=[%d] ", tmp->operateur);
		tmp = tmp->next;
		i++;
	}
	fprintf(stderr, "\n");
}

void prrr(t_cmd_parse *cmd_parse, int ok)  // show final list
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

int	copy_name(t_main *data, char *tmp, int i)
{
	int j;
	int k;

	j = 0;
	k = 0;
	while (data->env_bis[i][j] != '=')
	{
		tmp[j] = data->env_bis[i][j];
		j++;
		k++;
	}
	tmp[k++] = '=';
	tmp[k++] = '"';
	j++;
	while (data->env_bis[i][j])
	{
		tmp[k] = data->env_bis[i][j];
		j++;
		k++;
	}
	tmp[k++] = '"';
	return (k);
}

void	copy_env(t_main *data, char *decla)
{
	int i;
	int j;
	int size;
	char *tmp;

	i = 0;
	while (data->env_bis[i])
	{
		j = 0;
		size = ft_strlen(data->env_bis[i]);
		tmp = malloc(sizeof(char) * (size + 2) + 1);
		if (!tmp)
			exit (1);
		j += copy_name(data, tmp, i);
		tmp[j] = '\0';
		data->env_exp[i] = ft_strjoin(decla, tmp);
		free(tmp);
		i++;
	}
	data->env_exp[i] = 0;
}

void    get_env_export(t_main *data)
{
	int 	i;
	char	 *decla;

	i = 0;
	decla = "declare -x ";
	while (data->env_bis[i])
		i++;
	data->env_exp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->env_exp)
		exit (1);
	i = 0;
	copy_env(data, decla);
}

void	get_env(t_main *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env_bis = (char **)malloc(sizeof(char *) * (i + 1));
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
