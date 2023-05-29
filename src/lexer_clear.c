/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 03:29:44 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/29 05:46:43 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lexer_del_first(t_lexer **lst)
{
	t_lexer	*tmp;

	tmp = *lst;
	*lst = tmp->next;
	lexerclear_one(&tmp);
	if (*lst)
		(*lst)->prev = NULL;
}

t_lexer	*lexerclear_one(t_lexer **lst)
{
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void	ft_lexerdelone(t_lexer **lexer_list, int id)
{
	t_lexer	*tmp;
	t_lexer	*prev;
	t_lexer	*start;

	start = *lexer_list;
	tmp = start;
	if ((*lexer_list)->i == id)
	{
		lexer_del_first(lexer_list);
		return ;
	}
	while (tmp && tmp->i != id)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp)
		prev->next = tmp->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	lexerclear_one(&tmp);
	*lexer_list = start;
}
