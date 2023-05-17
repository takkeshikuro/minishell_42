/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 05:04:38 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/17 05:42:34 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	pid_t			pid;
	int				infile;
	int				outfile;
	int				*pipe_fd;
	char			*paths;
	char			**cmd_paths;
	char			**cmd_args;
	char			*cmd;
	char			*argv[];
}					t_pipex;

typedef enum s_tokens
{
	PIPE = 1,
	RIGHT,
	RIGHT_RIGHT,
	LEFT,
	LEFT_LEFT,
}					t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

/* typedef struct s_parser_tools
{
	t_lexer			*lexer_list;
	t_lexer			*redirections;
	int				num_redirections;
	struct s_main	*data;
}	t_parser_tools; */

typedef struct s_main
{
	int				ok;
	int				pipe_count;
	char			*input_line;
	char			**tab_input_blank;
	t_pipex			*pipex;
	char			*test;
	t_lexer			*lexer_list;
}					t_main;

// main.c
int				mini_loop(t_main *data, char **env);
void				parsing(t_main *data, char **env);

//lexer.c
int				go_lexer(t_main *data);
t_tokens			is_token(int c);
int					add_token(char *str, int i, t_lexer **lexer_list);
int					add_word(char *str, int i, t_lexer **lexer_list);
int					add_to_list(char *str, t_tokens token,
						t_lexer **lexer_list);

// lexer_utils.c
t_lexer				*ft_lexernew(char *str, int token);
void				ft_lexeradd_back(t_lexer **lst, t_lexer *new);

// utils.c
void				free_tab(char **tab);
int					error(char *s);
int					ft_nbstr(char const *str, char sep);
void				void_error(char *s);
int					is_space(char c);

// pipe_manage.c
int					contains_char(char *str, char c);
char				*get_command(char **paths, char *cmd);
char				*find_path(char **envp);
void				close_pipe(t_main *data);
void				duplicate2(int input, int output);
void				child_process(t_main *data, char **envp, int pos);
void				wait_childs(t_main *data);
void				pipe_init(t_main *data, char **env);
void				parent_free(t_pipex *pipex);
void				pipe_manage(t_main *data, char **env);

//builtins echo.c
int					how_much_quote(const char *str, int sep);
void				cpy_into_sep(char *src, char *dest, char sep);
void				quote_stuff(t_main *data, int sep);
void				option_is_here(t_main *data, int ac, int id_arg);
void				no_option_here(t_main *data, int ac);
int					check_option(t_main *data, int nb_s);
void				builtin_echo(t_main *data);

#endif