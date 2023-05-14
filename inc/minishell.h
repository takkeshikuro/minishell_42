/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 05:04:38 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/14 08:22:57 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_main
{
    int ok;
    char    *input_line;
    char    **tab_input_blank;
}   t_main;

int	error(char *s);
int	ft_nbstr(char const *str, char sep);


void	cpy_into_sep(char *src, char *dest, char sep);
int	how_much_quote(const char *str, int sep);
void    quote_stuff(t_main *data, int sep);
void	builtin_echo(t_main *data);


#endif