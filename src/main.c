/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 03:45:35 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/31 07:44:37 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* void	parsing(t_main *data, char **env)
{
	int	i;
	int	j;

	i = 0;
	(void)env;
	data->tab_input_blank = ft_split(data->input_line, ' ');
	while (data->input_line[i])
	{
		if (!ft_strncmp(data->input_line, "echo", 4))
		{
			builtin_echo(data);
			break ;
		}
		i++;
	}
	free_tab(data->tab_input_blank);
} */


void    parsing(t_main *data, char **env)
{
	int i;

	i = 0;
	data->pipe_count = 0;
	while (data->input_line[i])
	{
		if (data->input_line[i] == '|' && data->input_line[i + 1] != '|'
			&& data->input_line[i - 1] != '|')
			data->pipe_count++;
		i++;
	}
	data->tab_input_blank = ft_split(data->input_line, '|');
	pipe_manage(data, env);
}

void prrr(t_cmd_parse *cmd_parse)
{
	t_cmd_parse *tmp;
	int i;

	tmp = cmd_parse;
	printf("tableau envoye a exec :\n");
	while (tmp)
	{
		i = 0;
		while (tmp->cmd_tab[i])
		{
			printf("[%s]\n", tmp->cmd_tab[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

void	start_in_loop(t_main *data, char *input)
{
	data->input_line = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!data->input_line)
		error("malloc failed");
	ft_strlcpy(data->input_line, input, ft_strlen(input));
	if (!how_much_quote(input, 34) || !how_much_quote(input, 39))
		exit_bash_error("quote error");
	if (!go_lexer(data))
		exit_bash_error("lexing failed.");
	ft_putendl_fd("[main check] fin lexing", 1);
	pr(data->lexer_list); // check lexer list before parsing
	go_parser(data);
	ft_putendl_fd("[main check] fin parsing", 1);
	pr(data->lexer_list); // check lexer list after parsing
	//if (!quote_manage(data) || quote_manage(data) == 2)
	//	expanding(data);
	
}

int	mini_loop(t_main *data, char **env)
{
	int		work;
	char	*input;

	work = 1;
	while (work)
	{
		input = readline("$>");
		if (input[0] != '\0')
		{
			start_in_loop(data, input);
			add_history(input);
			parsing(data, env);
			wait_childs(data);
			//prrr(data->cmd_parse); check cmd parse list tab
			free(input);
			free(data->input_line);
		}
		if (ft_strnstr(input, "exit", 4) != 0)
			work = 0;
	}
	if (data->tab_input_blank)
		free_tab(data->tab_input_blank);
	clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_main	data;

	(void)av;
	if (ac != 1)
		return (error("run ./minishell without arg"));
	if (!env[0])
		return (error("env"));
	mini_loop(&data, env);
	return (0);
}

//in the while :(idk if important)
// Check for EOF.
// if (!data.full_line)
//     break ;