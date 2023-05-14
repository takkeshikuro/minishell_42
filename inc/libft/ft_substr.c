/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:56:35 by tmorikaw          #+#    #+#             */
/*   Updated: 2022/11/23 09:59:14 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char		*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (len != 0)
		ft_strlcpy(str, s + start, len + 1);
	else
		*str = 0;
	return (str);
}

/* int	main()
{
	char *str = "takeshikuro";
	//int	start = 2;
	//int	len = 3;
	printf(" %s", ft_substr(str, 3, 2));
} */