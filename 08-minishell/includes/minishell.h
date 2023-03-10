/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 11:38:38 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "commands.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <dirent.h>
# include <termios.h>
# include <signal.h>
# include <errno.h>
# include <curses.h>
# include <term.h>

typedef struct global_util
{
	char		**here_doc;
	char		**tokens;
	t_command_q	*command_q;
	size_t		i;
	size_t		x;
}	t_global_util;

t_global_util	g_utils;

//	Prompt
void		routine_prompt(t_command_q *command_q);
void		ft_prompt_signal(t_command_q *command_q);
void		ft_parsing_failed(t_command_q *command_q, char *entry);
void		ft_parsing_succes(t_command_q *command_q, char *entry);

//	Engine
void		engine(t_command_q *command_q);
void		builtins_engine(t_command	*command, int *process_tab);
void		command_engine(t_command *command);
void		ft_fdsetup(t_command *command);
void		ft_close_all_fd(t_command *command);
void		ft_add_pipe(t_command *command);
void		update_exit_status(t_command_q *command_q);

//	Heap to stack convertion
const char	**strings_tostack(char **strs);
const char	*string_tostack(char *str);
size_t		strmax_size(char **envp);
size_t		len_max(char **envp);

//	Parsing functions
bool		parsing(t_command_q *command_q, char *entry);
char		**split_entry(char *entry, int nb_node);
char		*get_word(char *string, size_t *i);
char		*get_char(char c, size_t *i);
bool		analyse_entry(t_command_q *command_q,
				char ***split_entry, int nb_node);
bool		command_exept(t_command_q *command,
				char **split_entry, size_t *i, size_t *length);
bool		init_cmd(t_command *command, char **split_entry,
				size_t *i, size_t *length);
bool		builtins_exept(t_command_q *command_q,
				char **split_entry, size_t *i, size_t *length);
void		parse_builtins(t_command *command, char **split_entry, size_t *i);
void		ft_remove_space(char ***split_entry);
void		ft_clear(char ***split_entry, size_t *len, size_t *temp);
bool		single_quotes_except(char **string, size_t *index);

//	Expand
bool		expand_envar(t_command *command, char ***split_entry, size_t i);
bool		expand_node(char **string, t_command *command);
bool		expand_var(char **string, int pos, t_command *command, bool hd);
bool		ft_ismetaenv(char c);
size_t		varlen(char *string);
bool		error_quotes(void);
bool		is_closed(char *string, char c);
void		ft_clear_var(char *str, size_t limit);
char		*getex(char *string, size_t start, size_t len, char **envp);
void		ft_free_trash(char **string, char *ex, char *new_str);
void		ft_boucle_hd(char *string, size_t *i, size_t pos, char *new_str);
void		ft_boucle(char **string, size_t *i, size_t pos, char *new_str);
size_t		get_offset(char *string, size_t start, size_t len, bool hd);
char		**expand_hd(char **here_doc, t_command *command);

//	Redirection
bool		ft_redir(t_command *command, char ***split_entry,
				size_t *length, size_t *i);
bool		ft_input(t_command *command, size_t *temp,
				size_t *len, char ***split_entry);
bool		ft_input_hd(t_command *command, size_t *temp,
				size_t *len, char ***split_entry);
bool		parse_output(t_command *command, char ***split_entry,
				size_t *len, size_t *i);
bool		ft_append(t_command *command, size_t *temp,
				size_t *len, char ***split_entry);
bool		ft_output(t_command *command, size_t *temp,
				size_t *len, char ***split_entry);

//	Utils
bool		ft_is_metacharacter(char c);
bool		ft_is_metacharacter_plus(char c);
size_t		word_size(char *string);
int			how_much_node(char *string);
bool		is_white_space(char *string);
char		**error_exit(char **s_entry);
size_t		how_much_node_in_command(char **split_entry);
void		ft_freeall(t_command *command);

//	Builtins
bool		is_builtins(char *string);
bool		is_option(char *str);
void		builtin_cd(t_command *command);
void		builtin_echo(t_command *command);
void		builtin_env(t_command *command);
void		builtin_exit(t_command *command);
void		builtin_export(t_command *command);
void		builtin_pwd(t_command *command);
void		builtin_unset(t_command *command);
void		builtin_status(t_command *command);

//	Commands fucntions
t_command	*last_command(t_command_q *command_q);
void		initialise_commands(t_command_q *command_q);
t_command	*new_command(t_command_q *command_q);
void		free_command(t_command	*command);
size_t		index_to_path(char **envp);
bool		path_is_valid(char *command, char **path, t_command_q *command_q);

//	Environnement fonctions
char		**envp_init(char **envp);
char		*find_variable(char *str, char **envp);
int			find_variable_index(char *str, char **envp);
void		change_pwd(char *pwd, char **envp);
size_t		get_envp_size(char **envp);
void		update_envar(t_command_q *command_q, char *str);

//	Signals Funtions
void		sig_handler(int signum);
void		signals(void);
void		sigcancel(void);
void		sig_handler_heredoc(int signum);
void		sig_chuttt(void);

//	Fonction pour libft ?
char		**ft_realloc(char **strings, char *str);
char		**ft_reallocs_pos(char **strings, char **str, int pos);
char		**ft_rev_realloc(char **array, void *ptr);
char		**ft_strsdup(char **strs);
char		*ft_strdecale(char *str);
void		ft_create_file(char **strings, char *name);
void		ft_delete_file(char *name);

#endif
