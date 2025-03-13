/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:59:34 by gougier           #+#    #+#             */
/*   Updated: 2025/03/11 11:11:05 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_test(int fd)
{
	if (fd > 1)
		close(fd);
}

void	close_unused_pipe(t_minishell *minishell)
{
	t_list_cmd	*curr_node;

	curr_node = minishell->list_cmd;
	while (curr_node)
	{
		close_test(curr_node->pipe[0]);
		close_test(curr_node->pipe[1]);
		curr_node = curr_node->next;
	}
}

void	close_in_parent(t_minishell *minishell)
{
	t_list_cmd	*curr_node;

	curr_node = minishell->list_cmd;
	while (curr_node)
	{
		close_test(curr_node->pipe[0]);
		close_test(curr_node->pipe[1]);
		curr_node = curr_node->next;
	}
}

void	restore_std(t_minishell *minishell)
{
	if (minishell->stdout_temp != STDOUT_FILENO)
		if (dup2(minishell->stdout_temp, STDOUT_FILENO) == -1)
			free_all_exit(minishell, "dup2 fail");
	if (minishell->stdin_temp != STDIN_FILENO)
		if (dup2(minishell->stdin_temp, STDIN_FILENO) == -1)
			free_all_exit(minishell, "dup2 fail");
}
