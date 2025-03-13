/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:03:53 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 10:18:40 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	filemode_append(int fd_out, t_redir *redir)
{
	if (fd_out != -1)
		close_test(fd_out);
	fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
	{
		perror(redir->filename);
		return (ERROR);
	}
	return (fd_out);
}

int	filemode_outredir(int fd_out, t_redir *redir)
{
	if (fd_out != -1)
		close_test(fd_out);
	fd_out = open (redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror(redir->filename);
		return (ERROR);
	}
	return (fd_out);
}

int	filemode_inredir(int fd_in, t_redir *redir)
{
	if (fd_in != -1)
		close_test(fd_in);
	fd_in = open (redir->filename, O_RDONLY);
	if (fd_in < 0)
	{
		perror(redir->filename);
		return (ERROR);
	}
	return (fd_in);
}

void	redir_in_pipe(t_minishell *minishell, t_list_cmd *curr_node)
{
	if (minishell->flag_redir_out != 1)
	{
		if (!is_last_node(curr_node) && curr_node->next)
		{
			if (dup2(curr_node->pipe[1], STDOUT_FILENO) == -1)
				free_all_exit(minishell, "dup2=");
		}
	}
	if (minishell->flag_redir_in != 1)
	{
		if (!is_first_node(curr_node))
		{
			if (curr_node->prev->pipe[0] > 0)
				if (dup2(curr_node->prev->pipe[0], STDIN_FILENO) == -1)
					free_all_exit(minishell, "dup2=");
		}
	}
}
