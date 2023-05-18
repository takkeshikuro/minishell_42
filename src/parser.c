/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:55:37 by keshikuro         #+#    #+#             */
/*   Updated: 2023/05/19 00:23:15 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int go_parser(t_main *data)
{
    t_lexer *current;
    int nb_pipe;

    current = data->lexer_list;
    nb_pipe = 0;
    while (current != NULL)
    {
        if (current->token == 1)
            nb_pipe =+ 1;
        current = current->next;
    }
}
/////// IN PROGRESS