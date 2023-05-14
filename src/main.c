/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 03:45:35 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/14 06:03:27 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	error(char *s)
{
	printf("error : %s\n", s);
	return (1);
}

/* int	check_quote_is_closed(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i])
			{
				if (str[i] == '"')
					return (0);
				if (str[i + 1] == '\0')
					return (1);
				i++;
			}
		}
		i++;
	}
} */

void	builtin_echo(t_main *data)
{
	int i = 1;
	int	ac;

	ac = ft_nbstr(data->input_line, 32);
	while (i < ac)
	{
		printf("%s", data->tab_input_blank[i]);
		i++;
	}
	printf("\n");
}

void	parsing(t_main *data)
{
	int i;

	i = 0;
	data->tab_input_blank = ft_split(data->input_line, 32);
	while (data->input_line[i])
	{
		if (!ft_strncmp(data->input_line, "echo", 4))
		{
			builtin_echo(data);
			return ;
		}
		i++;
	}


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
		if (input[0] != '\0')
			add_history(input);
		//printf("%s", data.input_line);
		
		parsing(&data);
		if ((ft_strlen(input) == 4) && !ft_strncmp(input, "exit", 4))
			work = 0;
		free(input);
		free(data.input_line);
	}
	rl_clear_history();
	return (0);
}

//in the while :(idk if important)
		// Check for EOF.
       // if (!data.full_line)
       //     break;