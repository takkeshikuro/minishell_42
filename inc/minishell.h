/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 05:04:38 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/06/16 16:42:11 by keshikuro        ###   ########.fr       */
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
	char				**env_bis;
	int					return_value;
	
		
	char				**tab_input_blank;
	t_pipex				*pipex;
	int					*pipe_fd;
	char				*path;
	char				**cmd_paths;
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

// main.c & utils
void					mini_loop(t_main *data, char **env);
void					parsing(t_main *data, char **env);
void					start_in_loop(t_main *data, char *input);
void	pr(t_lexer *lexer_list);              // for lexer
void	prrr(t_cmd_parse *cmd_parse, int ok); //for parser
void					get_env(t_main *data, char **env);
void					pr_redir(t_lexer *lexer_list);
void	reset_stuff(t_main *data);

//lexer.c  && utils && clear
int						go_lexer(t_main *data);
t_operateurs			is_operateur(int c);
int						add_operateur(char *str, int i, t_lexer **lexer_list);
int						add_word(char *str, int i, t_lexer **lexer_list);
int						add_to_list(char *str, t_operateurs operateur,
							t_lexer **lexer_list);
t_lexer					*ft_lexernew(char *str, int operateur);
void					ft_lexeradd_back(t_lexer **lst, t_lexer *new);
void					rm_space(t_lexer *lst);
void					lexer_del_first(t_lexer **lst);
t_lexer					*lexerclear_one(t_lexer **lst);
void					ft_lexerdelone(t_lexer **lexer_list, int id);

// parser.c  && utils && redir
int						go_parser(t_main *data);
t_cmd_parse				*init_cmd(t_parser_data *p_data);
t_cmd_parse				*cmd_parse_new(char **tab, int num_redir,
							t_lexer *redirection);
int						count_pipe(char *s);
int						count_words(t_lexer *lexer_list);
void					small_check(t_main *data);
t_parser_data			init_p_data(t_lexer *lexer_list, t_main *data);
void					cmd_parseadd_back(t_cmd_parse **lst, t_cmd_parse *new);
void					redirection(t_parser_data *p_data);
void					add_redirection(t_lexer *tmp, t_parser_data *p_data);

// quote_manage.c  && utils
int	quote_manage(t_main *data, t_cmd_parse *node, int i);
int						rm_quote(t_cmd_parse *node, int i_tab, int quote);
char					*ft_strim(char const *s1, int quote);
int						check_set(char c, int quote);

// expander.c  && utils
void	expanding(t_main *data, t_cmd_parse *node, int i);
int					expand_dollard(t_main *data, t_cmd_parse *cmd_node,
							int nb_env, int j);
char					*go_find(char **env, char *s);
int					rm_dollard(t_cmd_parse *cmd_node, int i, int j);
int						check_env_variable(t_main *data, char *s, int j);
int						check_env_bis(char **env, char *str_dol);
char					*good_variable(char *s);
void	copy_past(t_cmd_parse *cmd_node, int i, int j_dol, char *str_replace);
							
char					*copy_without_dol(t_cmd_parse *node, int i, int j, char *s);
char	*keep_good_str(char **env, int nb_env);
char	*check_char_after(t_cmd_parse *node, int i, int j);



// utils.c
void					free_tab(char **tab);
int						error(char *s);
int						ft_nbstr(char const *str, char sep);
void					void_error(char *s);
int						is_space(char c);
void					exit_bash_error(char *s);

// pipe_manage.c
void					execute_cmd(t_main *data);
void					wait_childs(int count);

//  builtins.c
int						built_env(t_main *data, t_cmd_parse *cmd_parse);
int						built_pwd(t_main *data, t_cmd_parse *cmd_parse);
int						built_echo(t_main *data, t_cmd_parse *cmd_parse);
int						built_cd(t_main *data, t_cmd_parse *cmd_parse);
int						built_unset(t_main *data, t_cmd_parse *cmd_parse);
int	built_exit(t_main *data, t_cmd_parse *cmd_parse);


// signal.c
void    EOT_handler(t_main *data);
void	sig_handler(int sig);
void	init_signals(void);

//builtins echo.c

int						how_much_quote(const char *str, int sep);
void					quote_stuff(t_main *data, int sep);


void	init_stuff(t_main *data);
void	free_kill(t_main *data);

#endif