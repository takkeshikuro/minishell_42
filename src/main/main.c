/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 03:45:35 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/07/19 16:43:35 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	*global_int=NULL;
//probleme pour crtl-c   dans un cat (rl_redisplay)
// a gerer surement avec la global

// pb pour "ls |" (je pense pas quil faut gerer ce cas)
// add += 1 a SHLVL (env)

//leak list parser + env_bis/export 

// gerer return value
// refaire batterie test echo / refaire built_echo

void	handle_quote_n_expand(t_main *data)
{
	t_cmd_parse	*node;
	int			i;

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
	//pr(data->lexer_list);
	if (!go_parser(data))
		exit_bash_error("parsing failed.");
//	prrr(data->cmd_parse, 1);
	handle_quote_n_expand(data);
	//if (!ft_strncmp(data->cmd_parse->cmd_tab[0], "export", 6))
	//	built_export(data, data->cmd_parse);
	//else if (!ft_strncmp(data->cmd_parse->cmd_tab[0], "cd", 2))
	//	built_cd(data, data->cmd_parse);
	//prrr(data->cmd_parse, 0);
	//pr(data->lexer_list);
}

void	mini_loop(t_main *data, char **env)
{
	char	*input;

	while (42)
	{
		input = readline("[42] $> ");
		if (!input)
			eot_handler(data);
		if (check_space(input) && pb_quote(input, 34) && pb_quote(input, 39))
		{
			if (input[0] != '\0')
			{
				start_in_loop(data, input);
				execute_cmd(data);
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
		return (error("env is missing"));
	init_stuff(&data);
	get_env(&data, env);
	get_env_export(&data);
	mini_loop(&data, env);
	return (0);
}

//in the while :(idk if important)
// Check for EOF.
// if (!data.full_line)
//     break ;