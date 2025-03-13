/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:08:38 by gougier           #+#    #+#             */
/*   Updated: 2025/03/11 12:27:03 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_check(t_minishell *minishell, t_list_cmd *curr_node)
{
	if (our_builtins(curr_node, minishell) == TRUE)
	{
		close_test(curr_node->pipe[1]);
		close_test(curr_node->pipe[0]);
		our_builtins_exec(minishell, curr_node);
		minishell->flag_for_export = 0;
		exit(0);
	}
	else if (our_builtins(curr_node, minishell) == 2
		&& !is_last_node(curr_node))
	{
		close_test(curr_node->pipe[1]);
		close_test(curr_node->pipe[0]);
		exit (0);
	}
	else if (our_builtins(curr_node, minishell) == 2 && is_last_node(curr_node))
		exit(0);
}

void	parent_process(t_list_cmd *curr_node, t_minishell *minishell)
{
	(void)curr_node;
	close_in_parent(minishell);
	restore_std(minishell);
}

void	exit_child(t_minishell *minishell, t_list_cmd *curr_node, int flag)
{
	if (is_last_node(curr_node) && flag == 0)
	{
		unlink(".heredoc");
		close_test(curr_node->pipe[1]);
		exit(1);
	}
	else if (!is_last_node(curr_node) && flag == 0)
	{
		unlink(".heredoc");
		close_test(curr_node->pipe[1]);
		exit(0);
	}
	else if (flag == 1)
	{
		unlink(".heredoc");
		close_unused_pipe(minishell);
		exit(130);
	}
}

char	*check_access_dfl_path(t_minishell *minishell, char *cmd)
{
	char	*path_cmd;
	char	**pathtab;
	int		i;

	path_cmd = NULL;
	if (is_a_dir(cmd))
		return (NULL);
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	pathtab = ft_split(DEFAULT_PATH, ':');
	if (!pathtab)
		return (minishell->flag_no_path = 1, NULL);
	i = 0;
	while (pathtab[i])
	{
		path_cmd = ft_strjoinsep(pathtab[i], cmd, '/');
		if (!path_cmd)
			return (free_chartab(pathtab), NULL);
		if (access(path_cmd, F_OK) == 0)
			return (free_chartab(pathtab), path_cmd);
		free(path_cmd);
		i++;
	}
	free_chartab(pathtab);
	return (NULL);
}
