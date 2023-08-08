/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 05:04:38 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/08/08 16:47:41 by keshikuro        ###   ########.fr       */
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

// a normer :
// copy_past() in expander_dol_utils
// add_word() in lexer
// init_cmd() in parser

extern int	*global_int;

typedef struct s_here_doc
{
	int	fd[2];
	int	pos;
}				t_here_doc;

typedef enum s_operateurs
{
	DEFAULT,
	PIPE,
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
	int					pid_last;
	char				*input_line;
	int					pipe_count;
	t_lexer				*lexer_list;
	struct s_cmd_parse	*cmd_parse;
	char				**env_bis;
	char				**env_exp;
	int					return_value;
	int					hd_count;
	int					hd_pos;
	t_here_doc			*here_doc;
	char				**tab_input_blank;
	int					*pipe_fd;
	char				*path;
	char				**cmd_paths;
	char				*test;
	int					syntaxe_check;
}						t_main;

typedef struct s_cmd_parse
{
	char				**cmd_tab;
	int					(*builtin)(t_main *, struct s_cmd_parse *);
	int					num_redirection;
	char				*hd_file_name;
	t_lexer				*redirection;
	int					hd_check;
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
int						start_in_loop(t_main *data, char *input);
void					handle_quote_n_expand(t_main *data);
void					parsing(t_main *data, char **env);
//utils
void					get_env(t_main *data, char **env);
void					reset_stuff(t_main *data);
void					init_stuff(t_main *data);
void					get_env_export(t_main *data);


/*****************lexer DIRECTORY***********************/
int						go_lexer(t_main *data);
t_operateurs			is_operateur(int c);
int						add_operateur(char *str, int i, t_lexer **lexer_list);
int						add_word(char *str, int i, t_lexer **lexer_list);
int						add_to_list(char *str, t_operateurs operateur,
							t_lexer **lexer_list);
//utils
void	rm_space(t_lexer *lst);
int	count_doub_quote(char *str, int i);
int	count_simp_quote(char *str, int i);
int	different_add_w(char *s, int i, int nb_quote, int quote);
int	add_word_support(char *str, int i);
//listing
t_lexer					*ft_lexernew(char *str, int operateur);
void					ft_lexeradd_back(t_lexer **lst, t_lexer *new);
void					lexer_del_first(t_lexer **lst);
t_lexer					*lexerclear_one(t_lexer **lst);
void					ft_lexerdelone(t_lexer **lexer_list, int id);
/***********************************************************/


/*****************parser & expander DIRECTORY***********************/
int						go_parser(t_main *data);
t_cmd_parse				*init_cmd(t_parser_data *p_data, int nb_word);
t_cmd_parse				*cmd_parse_new(char **tab, int num_redir,
							t_lexer *redirection);
//parser ope/checking/redir
int						small_check(t_main *data);
int						ope_check(t_main *data);
int						check_single(t_main *data, t_lexer *current);
int						check_double(t_main *data, t_lexer *current);
int						check_rr(t_main *data, t_lexer *crt);
int						check_ll(t_main *data, t_lexer *crt);
int						check_p_r(t_main *data, t_lexer *tmp);
int						check_r(t_main *data, t_lexer *crt);
int						check_l(t_main *data, t_lexer *crt);
void					redirection(t_parser_data *p_data);
void					add_redirection(t_lexer *tmp, t_parser_data *p_data);
//syntax_manage
int						cmpchar(char c, char ok);
int						cp_s(char *tmp, char *s, int i);
int						syntax_dig_2(t_main *data, char *s, int i);
int						syntax_dig(t_main *data, char *s);
int						syntax_check(t_main *data, int size);

//parser utils random
int						count_pipe(char *s);
int						count_words(t_lexer *lexer_list);
int						lexer_size(t_lexer *lst);
t_parser_data			init_p_data(t_lexer *lexer_list, t_main *data);
void					cmd_parseadd_back(t_cmd_parse **lst, t_cmd_parse *new);

// quote_manage.c  && utils
int						quote_manage(t_main *data, t_cmd_parse *node, int i);
int						rm_quote(t_cmd_parse *node, int i_tab, int quote);
int						nb_qt(char *s, int quote);
char					*ft_strim(char const *s1, int quote);
int						check_set(char c, int quote);

// expander.c  && utils
void					expanding(t_main *data, t_cmd_parse *node, int i);
int						expand_dollard(t_main *data, t_cmd_parse *cmd_node,
							int nb_env, int j);
char					*go_find(char **env, char *s);
int						rm_dollard(t_cmd_parse *cmd_node, int i, int j);
int						check_env_variable(t_main *data, char *s, int j);
int						check_env_bis(char **env, char *str_dol);
char					*good_variable(char *s);
void					copy_past(t_cmd_parse *cmd_node, int i, int j_dol,
							char *str_replace);
char					*copy_without_dol(t_cmd_parse *node, int i, int j,
							char *s);
char					*keep_good_str(char **env, int nb_env);
char					*check_char_after(t_cmd_parse *node, int i, int j);
/***********************************************************/

/*****************EXEC DIRECTORY***********************/

// pipe_manage.c && utils
void					execute_cmd(t_main *data);
int						open_outfile(t_cmd_parse *node);
int						open_infile(t_cmd_parse *node);
int						contains_char(char *str, char c);
char					*get_command(char **paths, char *cmd);
int						lstsize(t_cmd_parse *lst);
char					*find_path(char **envp);
void					close_pipe(t_main *data, int count);
int						open_append(t_cmd_parse *node);
void					here_doc_manage(t_main *data, t_cmd_parse *node, int fd[2]);
//execbuiltin
void					builtin_exec(t_main *data, t_cmd_parse *node);
void					builtin_exec_2(t_main *data, t_cmd_parse *node, char *cmd);
void					builtin_exec_3(t_main *data, t_cmd_parse *node, char *cmd);
int						first_builtins(t_main *data, t_cmd_parse *node);

//hd.c
int						has_variable(char *input);
int						ft_varname_len(char *str);
char					*get_var_name(char *input);
char					*get_var_content(t_main *data, char *var_name);
void					here_doc_manage(t_main *data, t_cmd_parse *node, int fd[2]);
void					here_doc_init(t_main *data, t_cmd_parse *node);

void					no_command(t_main *data, t_cmd_parse *node);
void					pipe_init(t_main *data, t_cmd_parse *node);

void					redir_pipe(t_main *data, t_cmd_parse *node, int *in, int *out);
void					last_redir(t_main *data, t_cmd_parse *node, int *in, int *out);

void					ft_execve(t_main *data, t_cmd_parse *node, char *cmd);

/***********************************************************/


/////////////////  builtins.c  ////////////////////
int						built_env(t_main *data, t_cmd_parse *cmd_parse);
int						built_pwd(t_main *data, t_cmd_parse *cmd_parse);
int						built_echo(t_main *data, t_cmd_parse *cmd_parse);
int						built_cd(t_main *data, t_cmd_parse *cmd_parse);
int						built_unset(t_main *data, t_cmd_parse *cmd_parse);
int						built_exit(t_main *data, t_cmd_parse *cmd_parse);
int						built_export(t_main *data, t_cmd_parse *cmd_parse);
///// utils unset
void					copy_good_exp(t_main *data, char **tab);
void					copy_good_bis(t_main *data, char **tab);
char					**crt_exp(char **old_tab, char *s, int len);
char					**crt_bis(char **old_tab, char *s, int len);
///// export & utils
void					export_support(t_main *data, char *s);
void					add_total_stuff(t_main *data, char *s);
int						simple_check(char *s);
// check
int						check_v_exist_bis(t_main *data, char *s);
int						check_v_exist_exp(t_main *data, char *s);
// add & rm 
void					rm_variable_bis(t_main *data, int supp);
void					rm_variable_exp(t_main *data, int supp);
void					add_v_to_envexp(t_main *data, char *s);
void					add_to_bis(t_main *data, char *s);
int						show_env_exp(t_main *data);
// utils
int						cp_string_quoted(char *s1, char *s2);
char					*cp_string_name(char *s);
int						check_valid_identifier(char c);
int						equal_env(char *s);
int						print_error_export(char *s, int ok);


//////////// signal.c
void					eot_handler(t_main *data);
void					sig_handler(int sig);
void					init_signals(void);

//utils_random
int						check_space(char *s);
int						pb_quote(const char *str, int sep);
int						is_space(char c);
int						ft_nbstr(char const *str, char sep);

//free_stuff.c
void					free_tab(char **tab);
void					free_kill(t_main *data);
void					free_cmd_list(t_main *data);

//error.c
int						error(char *s);
void					void_error(char *s);
int						syntax_err(t_main *data, char *s);
int	is_dir_error(t_main *data, char *s, int ok);

// a supp
void					pr(t_lexer *lexer_list);              // for lexer
void					prrr(t_cmd_parse *cmd_parse, int ok); //for parser
void					pr_redir(t_lexer *lexer_list);

#endif