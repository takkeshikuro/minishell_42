/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_random2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 08:56:06 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/28 08:56:19 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*just_alloc(int len, int j_dol, char *s_af)
{
	char	*ok;

	if (s_af)
		ok = malloc(sizeof(char) * (j_dol + len + ft_strlen(s_af)) + 1);
	else
		ok = malloc(sizeof(char) * (j_dol + len) + 1);
	if (!ok)
		exit(1);
	return (ok);
}
