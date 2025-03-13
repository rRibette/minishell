/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_type.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:59:36 by rribette          #+#    #+#             */
/*   Updated: 2025/03/08 14:36:49 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISH_TYPE_H
# define MISH_TYPE_H

# define DEFAULT_PATH "/usr/local/sbin:/usr/local/bin:\
/usr/sbin:/usr/bin:/sbin:/bin"

typedef struct s_redir
{
	char			*filename;
	int				filemode;
	int				quoted;
	struct s_redir	*next;
}	t_redir;

typedef struct s_list_cmd
{
	char				*input;
	char				**arg;
	char				*cmd;
	int					index;
	char				*heredoc_file;
	t_redir				*redir_list;
	int					pipe[2];
	int					nb_arg;
	int					size_lst;
	struct s_list_cmd	*prev;
	struct s_list_cmd	*next;
}	t_list_cmd;

typedef enum e_tokid
{
	WORD,
	FILENAME,
	CMD,
	ASSIGNMENT,
	CMDARG,
	PIPE,
	HERE_DOC,
	QUOTED_FILENAME,
	APPEND,
	OUTREDIR,
	INREDIR
}	t_tokid;

typedef struct s_token
{
	t_tokid			id;
	char			*str;
	int				toklen;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	int				index;
	char			*data;
	char			*var;			
	char			*subst;			
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	int			exit_code;
	int			flag_redir_out;
	int			flag_redir_in;
	int			flag_no_path;
	int			flag_for_export;
	char		*default_home;
	int			heredoc;
	int			shlvl;
	int			default_param;
	int			stdout_temp;
	int			stdin_temp;
	t_env		*assign_tab;
	t_list_cmd	*list_cmd;
	t_env		*env;
}	t_minishell;

#endif
