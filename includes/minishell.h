/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:24:04 by gougier           #+#    #+#             */
/*   Updated: 2025/03/11 12:48:23 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700 //to make sigaction work
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parsing.h"
# include "mish_type.h"
# define ERROR -1
# define SUCCESS 1
# define TRUE 1
# define FALSE 0
# define READ 0
# define WRITE 1
# define APPEND 2
# define HERE_DOC 0
# define INREDIR 1
# define APPEND 2
# define OUTREDIR 3

extern volatile sig_atomic_t	g_signal_flag;

/* builtins */

int			our_builtins(t_list_cmd *curr_node, t_minishell *minishell);
void		our_builtins_exec(t_minishell *minishell, t_list_cmd *curr_node);
void		our_builtins_exec_in_child(t_minishell *minishell);
void		ft_pwd(t_minishell *minishell);
void		ft_exit(t_minishell *minishell, t_list_cmd *curr_node);
void		ft_cd(t_minishell *minishell, t_list_cmd *curr_node);
char		*get_home(t_minishell *minishell, int init);
void		ft_export(t_minishell *minishell, t_list_cmd *curr_node);
void		export_with_arg(t_minishell *minishell, t_list_cmd *curr_node);
void		ft_env(t_minishell *minishell, t_list_cmd *curr_node);
t_env		*create_element(char *content);
t_env		*find_existing_node(t_env *env, char *str);
void		append_element(t_env *env, t_env *element);
void		update_oldpwd(t_minishell *minishell);
void		final_export(t_minishell *minishell, char *str);
void		ft_unset(t_minishell *minishell, t_list_cmd *curr_node);
void		ft_echo(t_minishell *minishell, t_list_cmd *curr_node);

/* debug */

void		print_array(char **array);
void		print_list_env(t_env *list);

/* error_free */

//error_msg.c
void		error_msg(t_minishell *minishell, char *str);
int			file_exist(char *path);
void		exit_error_msg(char *str);
void		cd_error_msg(char *str);
void		execve_fail(t_minishell *minishell, char *path);
void		export_error_msg(char *str, t_minishell *minishell);
void		join_cmd_error_msg(t_minishell *minishell, char *cmd, char *error);
//free.c
char		**free_array(char **array);
t_env		*free_list_env(t_env *lst_cmd, int dup);
int			is_a_dir(char *path);
//free2.c
void		close_fd_temp(t_minishell *minishell);
void		no_path_case(t_minishell *minishell, t_list_cmd *curr_node);
int			free_and_quit_error(char *line, int fd_temp);

/* env */

//get_path.c
char		**get_paths(char **envp);
char		**path_env(t_env *env);
//env_utils.c
t_env		*create_env_node(char *var, int dup);
int			var_len(char *var);
t_env		*check_node(t_env *node, int dup);
void		free_node(t_env *node, int dup);
t_env		*append_node(char *node_str, t_env *head, int dup);
//env_utils2.c
t_env		*change_node(t_env *node, char *str);
t_env		*remove_node(t_env *node, t_env *head);
void		print_node(t_env *node);
void		print_env(t_env *env);

/* exec */

//heredoc.c
int			make_here_doc(t_minishell *minishell,
				char *limiter, t_redir *redir, char *heredoc_file);
char		*get_heredoc_name(t_list_cmd *curr_node);
void		exec(t_minishell *minishell);
void		create_child_p(t_minishell *minishell, t_list_cmd *curr_node,
				pid_t *array_pid, int i);
int			loop_heredoc(t_minishell *minishell, t_list_cmd *head);

//redirections.c
int			here_doc_redir(char *limiter, t_minishell *minishell,
				t_redir *redir, t_list_cmd *curr_node);
int			redirection(t_minishell *minishell, t_list_cmd *curr_node);

//signals.c
void		signal_handler(void);
void		setup_sigchld_handler(void);
void		signal_handler_after_rl(void);
void		sig_handler_in_child(void);
void		check_signal(t_minishell *minishell);
int			check_signal_hered(t_minishell *minishell);
void		sig_handler_in_heredoc(void);
void		handle_ctrl_bcksl(void);
void		signal_in_parent(void);
void		routine_heredoc(int signal);

//update_shlvl.c
void		update_shlvl(t_minishell *minishell, char *str);
void		check_shlvl(t_minishell *minishell, t_list_cmd *curr_node);

//open_close.c
void		restore_std(t_minishell *minishell);
void		close_unused_pipe(t_minishell *minishell);
void		close_in_parent(t_minishell *minishell);
void		close_test(int fd);

//waitpid.c
void		waitpid_loop(t_minishell *minishell, pid_t *array_pid);

//create_process_2.c
void		builtins_check(t_minishell *minishell, t_list_cmd *curr_node);
void		parent_process(t_list_cmd *curr_node, t_minishell *minishell);
void		exit_child(t_minishell *minishell, t_list_cmd *curr_node, int flag);
char		*check_access_dfl_path(t_minishell *minishell, char *cmd);

//redirections_2.c
int			filemode_append(int fd_out, t_redir *redir);
int			filemode_outredir(int fd_out, t_redir *redir);
int			filemode_inredir(int fd_in, t_redir *redir);
void		redir_in_pipe(t_minishell *minishell, t_list_cmd *curr_node);

/* utils */

//create_list_env.c
char		**put_list_to_array(void *lst);
t_env		*create_empty_env(t_minishell *minishell);
t_env		*create_env(t_minishell *minishell, char **envp);
//create_list_cmd.c
char		**lst_to_arr_cmd(void *lst);
//init.c
char		*get_pwd(t_minishell *minishell);
void		init_all(t_minishell *minishell, char **envp);
void		init_stdtemp(t_minishell *minishell);
//utils.c
long		ft_atol(char *s);
char		*ft_strndup(char *s, int n);
int			ft_strcmp(char *s1, char *s2);
int			is_last_node(t_list_cmd *lst);
int			is_first_node(t_list_cmd *lst);

#endif
