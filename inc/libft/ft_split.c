/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:57:30 by tmorikaw          #+#    #+#             */
/*   Updated: 2022/11/24 19:09:51 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **tab, int nbcase)
{
	int	i;

	i = 0;
	while (i < nbcase)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	ft_nbstr(char const *str, char sep)
{
	int	i;
	int	nbword;

	i = 0;
	nbword = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
			nbword++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (nbword);
}

static char	*words(const char *s, char sep)
{
	int		j;
	char	*word;

	j = 0;
	while (s[j] && s[j] != sep)
		j++;
	word = ft_substr(s, 0, j);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	char	*word;
	int		i;
	int		nbstr;

	nbstr = ft_nbstr(s, c);
	i = 0;
	array = malloc(sizeof(char *) * (nbstr + 1));
	if (!array || s == NULL)
		return (NULL);
	while (*s && i < nbstr)
	{
		while (*s && *s == c)
			s++;
		word = words(s, c);
		if (!word)
			return (free_all(array, i));
		s = s + ft_strlen(word);
		array[i++] = word;
	}
	array[nbstr] = 0;
	return (array);
}

/* int	main(int ac, char **av)
{
	char **tab;
	int i = 0;
	tab = ft_split(av[1], ' ');
	if (!tab)
		return (1);
	if (ac != 1)
	{
		while (tab[i])
		{
			printf("%s\n", tab[i]);
			free(tab[i]);
			i++;
		}
	}
	free(tab);
	return (0);
} */
