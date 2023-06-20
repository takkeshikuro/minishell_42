/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 03:45:35 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/20 02:30:56 by tmorikaw         ###   ########.fr       */
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


//probleme pour crtl-c   dans un cat (rl_redisplay)
//idem pour crtl-backslash dans cat
//probleme d'espace pour <echo "ok $ok ok">
//probleme de prompt desfois (random)
//mettre <minishell: command not found: cmd> pour cmd invalide 
//link les builtins a l'execution


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

void	handle_quote_n_expand(t_main *data)
{
	t_cmd_parse *node;
	int 		i;

	node = data->cmd_parse;
	while (node)
	{
		i = 0;
		while (node->cmd_tab[i])
		{
			if (!quote_manage(data, node, i))
				expanding(data, node, i);
			i++;
		}
		node = node->next;
	}
}


void	start_in_loop(t_main *data, char *input)
{
	data->input_line = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!data->input_line)
		error("malloc failed");
	ft_strlcpy(data->input_line, input, ft_strlen(input));
	if (!go_lexer(data))
		exit_bash_error("lexing failed.");
//	pr(data->lexer_list);
	if (!go_parser(data))
		exit_bash_error("parsing failed.");
//	prrr(data->cmd_parse, 1);
	handle_quote_n_expand(data);
 	if (!ft_strncmp(data->cmd_parse->cmd_tab[0], "exit", 4))
		built_exit(data, data->cmd_parse);
	if (!ft_strncmp(data->cmd_parse->cmd_tab[0], "cd", 2))
		built_cd(data, data->cmd_parse);
///	prrr(data->cmd_parse, 0);
}



void	mini_loop(t_main *data, char **env)
{
	char	*input;

	while (42)
	{
		input = readline("$>");
		if (!input)
			EOT_handler(data);
		if (check_space(input) && pb_quote(input, 34) && pb_quote(input, 39))
		{
			if (input[0] != '\0')
			{
				start_in_loop(data, input);
				//parsing(data, env);
				execute_cmd(data);
				//wait_childs(data->pipe_count);
				reset_stuff(data);
			}
		}
		add_history(input);
		free(input);
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