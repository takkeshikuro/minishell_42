/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main (2).c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 03:45:35 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/16 21:06:51 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	error(char *s)
{
	printf("error : %s\n", s);
	return (1);
}

void	void_error(char *s)
{
	printf("error : %s\n", s);
	return ;
}

/*void	parsing(t_main *data, char **env)
{
	int i;

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

}*/

void    parsing(t_main *data, char **env)
{
	int	i;

	i = 0;
	data->pipe_count = 0;
	while (data->input_line[i])
	{
		if (data->input_line[i] == '|' && data->input_line[i + 1] != '|' && data->input_line[i - 1] != '|')
			data->pipe_count++;
		i++;
	} 
	data->tab_input_blank = ft_split(data->input_line, '|');
    pipe_manage(data, env);
}

int	main(int ac, char **av, char **env)
{
	t_main	data;
	int		work;
	char	*input;

	work = 1;
	(void)av;
	if (ac != 1)
		return (error("run ./minishell without arg"));
	if (!env[0])
		return (error("env"));
	while (work)
	{
		input = readline("$>");
		data.input_line = malloc(sizeof(char) * (ft_strlen(input) + 1));
		ft_strlcpy(data.input_line, input, ft_strlen(input));
		if (input[0] != '\0' && !ft_strnstr(input, "exit", 4))
        {
		    add_history(input);
		    parsing(&data, env);
        	wait_childs(&data);
        }
		if (ft_strnstr(input, "exit", 4) != 0)
			work = 0;        
		free(input);
		free(data.input_line);

	}
    if (data.tab_input_blank)
       free_tab(data.tab_input_blank);
	clear_history();
	return (0);
}

//in the while :(idk if important)
		// Check for EOF.
	   // if (!data.full_line)
	   //     break;