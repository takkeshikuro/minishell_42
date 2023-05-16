/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell (2).h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 05:04:38 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/16 21:08:07 by keshikuro        ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
 
typedef struct s_pipex
{
	pid_t   pid;
	int     infile;
	int     outfile;
	int     *pipe_fd;
	char    *paths;
	char    **cmd_paths;
	char    **cmd_args;
	char    *cmd;
	char	*argv[];
}	t_pipex;

typedef struct s_main
{
	int ok;
	int     pipe_count;
	char    *input_line;
	char    **tab_input_blank;
	t_pipex	*pipex;
	char	*test;
}   t_main;

int	error(char *s);
int	ft_nbstr(char const *str, char sep);
void	void_error(char *s);


void	cpy_into_sep(char *src, char *dest, char sep);
int	how_much_quote(const char *str, int sep);
void    quote_stuff(t_main *data, int sep);
void	builtin_echo(t_main *data);
void	pipe_manage(t_main *data, char **env);
void	free_tab(char **tab);
void	wait_childs(t_main *data);
void    parent_free(t_pipex *pipex);



#endif