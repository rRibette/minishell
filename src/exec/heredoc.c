/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:41:56 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 12:33:37 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	msg_err_here_doc(char *str, t_minishell *minishell)
{
	char	*msg;

	msg = "warning: here-document delimited by end-of-file (wanted `";
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "')\n", 4);
	minishell->exit_code = 0;
	return (1);
}

static int	free_and_quit_no_error(char *line, int fd_temp,
	t_minishell *minishell)
{
	free(line);
	close (fd_temp);
	minishell->exit_code = 0;
	return (0);
}

int	make_here_doc(t_minishell *minishell, char *limiter,
	t_redir *redir, char *heredoc_file)
{
	int					fd_temp;
	char				*line;
	size_t				len;

	len = ft_strlen(limiter);
	fd_temp = open(heredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_temp < 0)
		free_all_exit(minishell, "open");
	sig_handler_in_heredoc();
	while (1)
	{
		line = readline("> ");
		if (check_signal_hered(minishell) == 1)
			return (free_and_quit_error(line, fd_temp));
		if (!line)
			return (close(fd_temp), msg_err_here_doc(limiter, minishell));
		line = find_dollar(line, minishell, redir->quoted);
		if (ft_strncmp(line, limiter, len) == 0 && line[len] == '\0')
			break ;
		ft_putendl_fd(line, fd_temp);
		free(line);
	}
	return (free_and_quit_no_error(line, fd_temp, minishell));
}

char	*get_heredoc_name(t_list_cmd *curr_node)
{
	char	*totstr;
	char	*hdidx;

	hdidx = ft_itoa(curr_node->index);
	if (!hdidx)
		return (NULL);
	totstr = ft_strjoin(".heredoc", hdidx);
	free(hdidx);
	return (totstr);
}

int	loop_heredoc(t_minishell *mish, t_list_cmd *head)
{
	t_redir		*redir;
	t_list_cmd	*curr_node;	
	int			f;

	f = 0;
	curr_node = head;
	while (curr_node)
	{
		redir = curr_node->redir_list;
		while (redir)
		{
			if (redir->filemode == HERE_DOC)
				f = here_doc_redir(redir->filename, mish, redir, curr_node);
			if (f == -2)
			{
				g_signal_flag = 0;
				return (-2);
			}
			redir = redir->next;
		}
		curr_node = curr_node->next;
	}
	return (0);
}
