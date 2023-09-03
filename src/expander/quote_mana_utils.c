/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_mana_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:30:04 by keshikuro         #+#    #+#             */
/*   Updated: 2023/08/30 03:12:32 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_set(char c, int quote)
{
	if (c == quote)
		return (1);
	return (0);
}

char	*ft_strim(char const *s1, int quote)
{
	char			*str;
	size_t			start;
	size_t			end;
	size_t			i;

	start = 0;
	while (s1[start] && check_set(s1[start], quote))
		start++;
	end = ft_strlen(s1);
	while (end > start && check_set(s1[end - 1], quote))
		end--;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = 0;
	return (str);
}
