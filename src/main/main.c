/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 03:45:35 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/13 08:44:11 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	free_kill(t_main *data)
{
	free_tab(data->env_bis);
	if (data->cmd_parse->cmd_tab)
		free_tab(data->cmd_parse->cmd_tab);
	if (data->input_line[0])
		free(data->input_line);
}

void	init_stuff(t_main *data)
{
	data->lexer_list = NULL;
	data->cmd_parse = NULL;
	init_signals();
}

void	reset_stuff(t_main *data)
{
	if (data->cmd_parse->cmd_tab[0])
		free_tab(data->cmd_parse->cmd_tab);
	if (data->input_line)
		free(data->input_line);
	init_stuff(data);
}


void	parsing(t_main *data, char **env)
{
	int	i;

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
	if (!go_parser(data))
		exit_bash_error("parsing failed.");
	if (!quote_manage(data))
		expanding(data);
 	if (!ft_strncmp(data->cmd_parse->cmd_tab[0], "exit", 4))
		built_exit(data, data->cmd_parse);
	//	else if (!ft_strncmp(data->cmd_parse->cmd_tab[0], "unset", 5))
	//		built_unset(data, data->cmd_parse);
	//	prrr(data->cmd_parse, 1);
	//	POUR TEST ECHO
}

void	mini_loop(t_main *data, char **env)
{
	int		work;
	char	*input;

	work = 1;
	while (work)
	{
		input = readline("$>");
		if (!input)
			EOT_handler(data);
		if (input[0] != '\0')
		{
			start_in_loop(data, input);
			add_history(input);
			//parsing(data, env);
			execute_cmd(data);
			//wait_childs(data->pipe_count);
			free(input);
			reset_stuff(data);
		}
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
	get_env(&data, env);
	init_stuff(&data);
	mini_loop(&data, env);
	return (0);
}

//in the while :(idk if important)
// Check for EOF.
// if (!data.full_line)
//     break ;