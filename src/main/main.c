/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 03:45:35 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/24 20:23:05 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// add += 1 a SHLVL (env)

//leak list parser + env_bis/export

// gerer return value
// return value apres un crtl-C (1 aulieu de 130)

// pb si input = 'NEW=okok' -> ne doit pas etre dans env_bis/exp

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

int	start_in_loop(t_main *data, char *input)
{
	data->input_line = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!data->input_line)
		error("malloc failed");
	ft_strlcpy(data->input_line, input, ft_strlen(input));
	if (!go_lexer(data))
		error("lexing failed.");
	if (!go_parser(data))
	{
		data->syntaxe_check = 1;
		return (1);
	}
	handle_quote_n_expand(data);
	return (0);
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
				if (!start_in_loop(data, input))
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
