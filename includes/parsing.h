/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 22:18:48 by rribette          #+#    #+#             */
/*   Updated: 2025/03/06 17:50:18 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "mish_type.h"

//tokenize.c
t_token		*tokenize(char *line, t_minishell *minishell);
int			find_eotok(char *line);
char		*find_dollar(char *line, t_minishell *minishell, int quoted);
void		find_quotes(char *line);
int			skip_spaces(char *line);

//token.c
t_token		*append_token(t_token *list, t_token *token,
				char *l, t_minishell *minishell);
void		print_token(t_token *token);
t_token		*create_token(char *line);

//tokenize_utils.c
int			ft_isspace(char c);
int			ft_isoperator(char *line);
int			remove_quotes(char *line);
int			find_next_quote(char *line, int print);
int			ft_strcmp(char *s1, char *s2);

//token_utils.c
int			is_redirtoken(t_token *token);
char		*ft_strldup(const char *str, int size);
int			is_redir_or_file(t_token *token);

//varsubst.c
char		*replace_dollar(char *line, int i, t_minishell *minishell);
char		*create_newline(char *line, char *var, int wordlen, int idx);
char		*get_var(t_minishell *minishell, char *line, int len, int idx);
char		*search_var(t_minishell *minishell, char *var);

//varsubst_utils.c
int			ft_varcmp(char *envline, char *var);
int			dollar_type(char *line);
char		*create_special_dollar(char *line, int idx, int len,
				t_minishell *minishell);		
char		*cpy_special_dollar(char *line, int idx, int totlen, int exit_code);

//varsubst_itoa.c
int			varsubst_intlen(int nb);
int			varsubst_itoa(char *line, int nb);

//parsing.c
t_list_cmd	*parse(char *line, t_minishell *minishell);
t_list_cmd	*fill_parsing(t_token *list, char *line, t_minishell *mish);
t_list_cmd	*init_list_cmd(char *l, t_token *lst, int i, t_minishell *mish);
t_list_cmd	*app_p(t_list_cmd *p, char *l, t_token *lst, t_minishell *msh);
void		get_lst_size(t_list_cmd *list);

//redir.c
t_redir		*get_redir(t_token *list, t_minishell *mish);
int			get_filemode(t_tokid id);
t_redir		*init_redir_node(char *str, t_minishell *minishell);
t_redir		*append_redir(t_redir *redir_list, t_redir *redir_node);
int			is_redir(t_token *token);

//syntax.c
int			check_syntax(t_token *list, char *line);

//categorize.c
void		categorize_token(t_token *token);
int			categorize_operator(t_token *token);
int			is_assignment(t_token *token);
int			is_quoted(char *str);

//cmdarg.c
t_token		*get_cmdargs(t_list_cmd *parsing, t_token *list, t_minishell *msh);
char		**init_cmdargs(t_token *list);
int			get_nbarg(t_token *list);

//cmdarg_split.c
char		**cmdargs_split(char *line);
int			cmdarg_cw(char *line);
int			append_word(char *line, char **table, int index);
int			cmd_len(char *line);

//cmdarg_utils.c
char		**cmdarg_dollar(char **cmdargs, t_minishell *minishell);
char		**cmdarg_line(char **cmdarg, int index, t_minishell *minishell);

//cmdarg_insert.c
char		**cmdarg_insert(char **cmdarg, int index);

//free_parsing.c
t_list_cmd	*return_free_parsing(t_list_cmd *parsing);
void		free_redir(t_redir *redir_list, int name_keep);
void		full_free_parsing(t_list_cmd *parsing);

//print_list_cmd.c
void		print_list_cmd(t_list_cmd *parsing);
void		print_list_cmd_node(t_list_cmd *parsing);
void		print_chartab(char **tab);
void		print_redir_list(t_redir *redir_list);
void		print_redir_mode(int filemode);

//free_token.c
t_token		*return_tokenize(char *line, t_token *list, t_token *token);
void		free_token_list(t_token *list, int str_keep);
void		exit_malloc(char *line, t_token *list,
				t_token *token, t_minishell *msh);
void		full_free_token(t_token *list);

//ft_strjoinsep.c
char		*ft_strjoinsep(char *str1, char *str2, char sep);

//assignment.c
void		handle_assigns(t_token *tok_list, t_minishell *minishell);

//chartab.c
char		**chartab_init(int len);
char		**free_chartab(char **chartab);
int			chartab_len(char **chartab);
char		**chartab_merge(char **tab1, char **tab2, int index);
char		*del_line(char **tab, int index);

//free.c (minishell.h)
void		free_all_exit(t_minishell *minishell, char *str);

#endif
