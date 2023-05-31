/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 05:04:38 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/31 05:26:22 by tmorikaw         ###   ########.fr       */
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
	pid_t				pid;
	int					infile;
	int					outfile;
	int					*pipe_fd;
	char				*paths;
	char				**cmd_paths;
	char				**cmd_args;
	char				*cmd;
	char				*argv[];
}						t_pipex;

typedef enum s_operateurs
{
	PIPE = 1,
	RIGHT,
	RIGHT_RIGHT,
	LEFT,
	LEFT_LEFT,
}						t_operateurs;

typedef struct s_lexer
{
	char				*str;
	t_operateurs		operateur;
	int					i;
	struct s_lexer		*next;
	struct s_lexer		*prev;
}						t_lexer;

typedef struct s_main
{
	int					ok;
	char				*input_line;
	int					pipe_count;
	t_lexer				*lexer_list;
	struct s_cmd_parse	*cmd_parse;
	
	char				**env_ok;
	char				**tab_input_blank;
	t_pipex				*pipex;
	char				*test;
}						t_main;

typedef struct s_cmd_parse
{
	char				**cmd_tab;
	int					(*builtin)(t_main *, struct s_cmd_parse *);
	int					num_redirection;
	char				*hd_file_name;
	t_lexer				*redirection;
	struct s_cmd_parse	*next;
	struct s_cmd_parse	*prev;
}						t_cmd_parse;

typedef struct s_parser_data
{
	t_lexer				*lexer_list;
	t_lexer				*redirection;
	int					num_redir;
	struct s_main		*data;
}						t_parser_data;

// main.c
int						mini_loop(t_main *data, char **env);
void					parsing(t_main *data, char **env);
void					start_in_loop(t_main *data, char *input);

//lexer.c
int						go_lexer(t_main *data);
t_operateurs			is_operateur(int c);
int						add_operateur(char *str, int i, t_lexer **lexer_list);
int						add_word(char *str, int i, t_lexer **lexer_list);
int						add_to_list(char *str, t_operateurs operateur,
							t_lexer **lexer_list);

// lexer_utils.c
t_lexer					*ft_lexernew(char *str, int operateur);
void					ft_lexeradd_back(t_lexer **lst, t_lexer *new);

// lexer_clear.c
void					lexer_del_first(t_lexer **lst);
t_lexer					*lexerclear_one(t_lexer **lst);
void					ft_lexerdelone(t_lexer **lexer_list, int id);

// parser.c
int						go_parser(t_main *data);
t_cmd_parse				*init_cmd(t_parser_data *p_data);
t_cmd_parse				*cmd_parse_new(char **tab, int num_redir,
							t_lexer *redirection);

// parser_utils.c
int						count_pipe(char *s);
int						count_words(t_lexer *lexer_list);
void					small_check(t_main *data);
t_parser_data			init_p_data(t_lexer *lexer_list, t_main *data);
void					cmd_parseadd_back(t_cmd_parse **lst, t_cmd_parse *new);

// expander.c
void					expanding(t_main *data);
void					expand_dollard(t_main *data, t_cmd_parse *cmd_node);
char					*go_find(char **env, char *s);
void					rm_dollard(t_main *data, t_cmd_parse *cmd_node);

// expander_utils.c
int						check_env_variable(t_main *data, char *s);
int						check_env_bis(char **env, char *str_dol);
char					*good_variable(char *s);
void					copy_past(t_cmd_parse *cmd_node, int i, int j, \
						char *str_replace);


// utils.c
void					free_tab(char **tab);
int						error(char *s);
int						ft_nbstr(char const *str, char sep);
void					void_error(char *s);
int						is_space(char c);
void					exit_bash_error(char *s);

// pipe_manage.c
int						contains_char(char *str, char c);
char					*get_command(char **paths, char *cmd);
char					*find_path(char **envp);
void					close_pipe(t_main *data);
void					duplicate2(int input, int output);
void					child_process(t_main *data, char **envp, int pos);
void					wait_childs(t_main *data);
void					pipe_init(t_main *data, char **env);
void					parent_free(t_pipex *pipex);
void					pipe_manage(t_main *data, char **env);

//builtins echo.c
int						how_much_quote(const char *str, int sep);
void					cpy_into_sep(char *src, char *dest, char sep);
void					quote_stuff(t_main *data, int sep);
void					option_is_here(t_main *data, int ac, int id_arg);
void					no_option_here(t_main *data, int ac);
int						check_option(t_main *data, int nb_s);
void					builtin_echo(t_main *data);

int						built_env(t_main *data, t_cmd_parse *cmd_parse);
int						built_pwd(t_main *data, t_cmd_parse *cmd_parse);

// echeck list
void	pr(t_lexer *lexer_list);

#endif