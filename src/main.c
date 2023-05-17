/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 03:45:35 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/17 06:23:31 by tmorikaw         ###   ########.fr       */
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

int	mini_loop(t_main *data, char **env)
{
	int		work;
	char	*input;

	work = 1;
	while (work)
	{
		input = readline("$>");
		data->input_line = malloc(sizeof(char) * (ft_strlen(input) + 1));
		if (!data->input_line)
			return (error("malloc failed"));
		ft_strlcpy(data->input_line, input, ft_strlen(input));
		if (!how_much_quote(data->input_line, 34)
			|| !how_much_quote(data->input_line, 39))
			return (error("quote ?"));
		if (!go_lexer(data))
			return (error("lexer"));
		if (input[0] != '\0' && !ft_strnstr(input, "exit", 4))
		{
			add_history(input);
			parsing(data, env);
			wait_childs(data);
		}
		if (ft_strnstr(input, "exit", 4) != 0)
			work = 0;
		free(input);
		free(data->input_line);
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