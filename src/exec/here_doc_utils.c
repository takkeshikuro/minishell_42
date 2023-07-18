/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:38:28 by rmarecar          #+#    #+#             */
/*   Updated: 2023/07/18 10:39:20 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_variable(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_varname_len(char *str)
{
	int	len;

	len = 1;
	while (str[len] > ' ' && str[len] < 127 && str[len] != '$')
		len++;
	return (len - 1);
}

char	*get_var_name(char *input)
{
	int		i;
	int		len;
	char	*name;

	i = 1;
	len = ft_varname_len(input);
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
	{
		fprintf(stderr, "ERROR MALLOC : GET VAR NAME (here_doc manage)");
		exit (1);
	}
	len = 0;
	while (input[i] != '$' && input[i] > ' ' && input[i] < 127)
	{
		name[len] = input[i];
		i++;
		len++;
	}
	name[len] = 0;
	return (name);
}
