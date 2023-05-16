/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 04:19:48 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/16 17:06:08 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	how_much_quote(const char *str, int sep)
{
	int	i;
	int	nb_quote;

	i = 0;
	nb_quote = 0;
	while (str[i])
	{
		if (str[i] == sep)
			nb_quote += 1;
		i++;
	}
	if (nb_quote % 2 == 0)
		return (1);
	else
		return (0);
}

void	cpy_into_sep(char *src, char *dest, char sep)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (src[i] != sep)
		i++;
	i += 1;
	while (src[i] != sep)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
}

void	quote_stuff(t_main *data, int sep)
{
	int		i;
	int		j;
	char	*into_quote;

	i = 0;
	j = 0;
	if (how_much_quote(data->input_line, sep))
	{
		while (data->input_line[i] != sep)
			i++;
		i += 1;
		while (data->input_line[i] != sep)
		{
			i++;
			j++;
		}
		into_quote = malloc(sizeof(char) * j + 1);
		cpy_into_sep(data->input_line, into_quote, sep);
		printf("%s", into_quote);
	}
	else
		return (void_error("quote"));
	free(into_quote);
	return ;
}

void	option_is_here(t_main *data, int ac, int id_arg)
{
	int i;
	if (data->tab_input_blank[id_arg][0] == 34)
		quote_stuff(data, 34);
	else if (data->tab_input_blank[id_arg][0] == 39)
		quote_stuff(data, 39);
	else 
	{
		i = id_arg;
		while (id_arg < ac)
		{
			if (id_arg > i)
				printf(" ");
			printf("%s", data->tab_input_blank[id_arg]);
			id_arg++;
		}
	}
}

void	no_option_here(t_main *data, int ac)
{
	int	i;

	if (data->tab_input_blank[1][0] == 34)
		quote_stuff(data, 34);
	else if (data->tab_input_blank[1][0] == 39)
		quote_stuff(data, 39);
	else
	{
		i = 1;
		while (i < ac)
		{
			if (i > 1)
				printf(" ");
			printf("%s", data->tab_input_blank[i]);
			i++;
		}
	}
}


int check_option(t_main *data, int nb_s)
{
	int i;

	if (data->tab_input_blank[nb_s][0] == '-')
	{
		i = 1;
		while (data->tab_input_blank[nb_s][i])
		{
			if (data->tab_input_blank[nb_s][i] != 'n')
				return (0);
			if (data->tab_input_blank[nb_s][i + 1] == '\0')
				return (1);
			i++;
		}	
	}
	else
		return (0);
}

void	builtin_echo(t_main *data)
{
	int ac;
	int i;

	ac = ft_nbstr(data->input_line, 32);
	if (ac == 1)
	{
		printf("\n");
		return ;
	}
	if (check_option(data, 1))
	{
		if (ac == 2)
			return ;
		i = 2;
		while (i <= ac)
		{
			if (!check_option(data, i))
				break ;
			i++;
			if (i == ac)
				return ;
		}
		option_is_here(data, ac, i);
		return ;
	}
	else
		no_option_here(data, ac);
	printf("\n");
}
