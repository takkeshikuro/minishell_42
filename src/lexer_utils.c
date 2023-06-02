 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 05:13:10 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/29 04:26:26 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_lexer	*ft_lexernew(char *str, int operateur)
{
	t_lexer		*new;
	static int	i;

//	i = 0;
	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		exit (1);
	new->str = str;
	new->operateur = operateur;
	new->i = i++;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lexeradd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	rm_space(t_lexer *lst)
{
	t_lexer	*tmp;
	int	i;
	
	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (tmp->str)
			tmp->str = ft_strtrim(tmp->str, " ");
		tmp = tmp->next;
	}
}
