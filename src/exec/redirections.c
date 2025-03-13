/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:49:27 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 11:14:23 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_redir(char *limiter, t_minishell *minishell,
		t_redir *redir, t_list_cmd *curr_node)
{
	char	*heredoc_file;

	if (!curr_node->heredoc_file)
		curr_node->heredoc_file = get_heredoc_name(curr_node);
	if (!curr_node->heredoc_file)
		free_all_exit(minishell, "malloc");
	heredoc_file = curr_node->heredoc_file;
	if (make_here_doc(minishell, limiter, redir, heredoc_file) == -2)
		return (-2);
	return (0);
}

static void	duplication(int fd_in, int fd_out, t_minishell *minishell,
		t_list_cmd *curr_node)
{
	if (fd_in != -1 && curr_node->cmd != NULL)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			free_all_exit(minishell, "dup2");
		unlink(".heredoc");
		minishell->flag_redir_in = 1;
	}
	if (fd_out != -1 && curr_node->cmd != NULL)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			free_all_exit(minishell, "dup2");
		minishell->flag_redir_out = 1;
	}
	if (fd_in != STDIN_FILENO)
		close_test(fd_in);
	if (fd_out != STDOUT_FILENO)
		close_test(fd_out);
}

static int	loop_in_out_append(t_redir *redir, int *fd_in, int *fd_out)
{
	while (redir)
	{
		if (redir->filemode == INREDIR)
		{
			*fd_in = filemode_inredir(*fd_in, redir);
			if (*fd_in == ERROR)
				return (ERROR);
		}
		else if (redir->filemode == OUTREDIR)
		{
			*fd_out = filemode_outredir(*fd_out, redir);
			if (*fd_out == ERROR)
				return (ERROR);
		}
		else if (redir->filemode == APPEND)
		{
			*fd_out = filemode_append(*fd_out, redir);
			if (*fd_out == ERROR)
				return (ERROR);
		}
		redir = redir->next;
	}
	return (0);
}

static int	redir_loop(t_minishell *minishell, t_redir *redir,
		t_list_cmd *curr_node)
{
	int		fd_in;
	int		fd_out;
	t_redir	*head;

	fd_in = -1;
	fd_out = -1;
	if (redir == NULL)
		return (0);
	head = redir;
	if (curr_node->heredoc_file != NULL)
		fd_in = open(curr_node->heredoc_file, O_RDONLY);
	redir = head;
	if (loop_in_out_append(redir, &fd_in, &fd_out) == ERROR)
		return (close_test(fd_out), close_test(fd_in), ERROR);
	duplication(fd_in, fd_out, minishell, curr_node);
	return (1);
}

int	redirection(t_minishell *minishell, t_list_cmd *curr_node)
{
	t_redir	*redir;
	int		error_nb;

	error_nb = 0;
	redir = curr_node->redir_list;
	error_nb = redir_loop(minishell, redir, curr_node);
	if (error_nb == ERROR)
		return (ERROR);
	else if (error_nb == -2)
		return (-2);
	redir_in_pipe(minishell, curr_node);
	close_unused_pipe(minishell);
	return (0);
}
