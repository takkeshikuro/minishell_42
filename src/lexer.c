/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 04:07:31 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/29 07:02:40 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	add_to_list(char *str, t_operateurs operateur, t_lexer **lexer_list)
{
	t_lexer	*node;

	node = ft_lexernew(str, operateur);
	if (!node)
		return (0);
	if (!lexer_list)
		*lexer_list = node;
	else
		ft_lexeradd_back(lexer_list, node);
	return (1);
}

int	add_word(char *str, int i, t_lexer **lexer_list)
{
	int	j;

	j = 0;
	while (str[i + j] && !is_space(str[i + j]) && !is_operateur(str[i + j]))
	{
		if (str[i + j] == 34)
		{
			j++;
			while (str[i + j] != 34 && str[i + j])
				j++;
			break ;
		}
		else if (str[i + j] == 39)
		{
			j++;
			while (str[i + j] != 39 && str[i + j])
				j++;
			break ;
		}
		else
			j++;
	}
	if (!add_to_list(ft_substr(str, i, j), 0, lexer_list))
		return (-1);
	return (j);
}

int	add_operateur(char *str, int i, t_lexer **lexer_list)
{
	t_operateurs	operateur;

	operateur = is_operateur(str[i]);
	if (operateur == RIGHT && is_operateur(str[i + 1]) == RIGHT)
	{
		if (!add_to_list(NULL, RIGHT_RIGHT, lexer_list))
			return (-1);
		return (2);
	}
	else if (operateur == LEFT && is_operateur(str[i + 1]) == LEFT)
	{
		if (!add_to_list(NULL, LEFT_LEFT, lexer_list))
			return (-1);
		return (2);
	}
	else if (operateur)
	{
		if (!add_to_list(NULL, operateur, lexer_list))
			return (-1);
		return (1);
	}
	return (0);
}

t_operateurs	is_operateur(int c)
{
	int				i;
	static int		tab_operateurs[3][2] = {
	{'|', PIPE},
	{'>', RIGHT},
	{'<', LEFT},
	};

	i = 0;
	while (i < 3)
	{
		if (tab_operateurs[i][0] == c)
			return (tab_operateurs[i][1]);
		i++;
	}
	return (0);
}

void	pr(t_lexer *lexer_list)
{
	t_lexer * tmp;
	int i = 0;

	printf("\n[CHECK LEXER] ");
	if (!lexer_list)
	{
		printf("lexer_list is clean\n");
		return ;
	}
	tmp = lexer_list;
	while (tmp)
	{
		printf("[node %d: ", i);
		if (tmp->str)
			printf("%s]", tmp->str);
		else
			printf("%d]", tmp->i);
		i++;
		tmp = tmp->next;
	}
}

int	go_lexer(t_main *data)
{
	int		i;
	int		j;

	i = 0;
	data->lexer_list = NULL;
	while (data->input_line[i])
	{
		j = 0;
		while (is_space(data->input_line[i]))
			i++;
		if (is_operateur(data->input_line[i]))
			j = add_operateur(data->input_line, i, &data->lexer_list);
		else
		{
			j = add_word(data->input_line, i, &data->lexer_list);
		}
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
