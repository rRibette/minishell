/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:00:26 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 13:33:08 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_access(t_minishell *minishell, char *cmd)
{
	char	*path_cmd;
	char	**pathtab;
	int		i;

	path_cmd = NULL;
	if (is_a_dir(cmd))
		return (NULL);
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	pathtab = path_env(minishell->env);
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

static void	exec_child_process(t_minishell *minishell, t_list_cmd *curr_node)
{
	char	*path;

	if (curr_node->cmd == NULL)
		free_all_exit(minishell, NULL);
	if (minishell->default_param == 1)
		path = check_access_dfl_path(minishell, curr_node->cmd);
	else
		path = check_access(minishell, curr_node->cmd);
	if (minishell->flag_no_path == 1)
		no_path_case(minishell, curr_node);
	if (path == NULL)
	{
		error_msg(minishell, curr_node->cmd);
		free_all_exit(minishell, NULL);
	}
	check_shlvl(minishell, curr_node);
	if (execve(path, curr_node->arg, put_list_to_array(minishell->env)) == -1)
		execve_fail(minishell, path);
}

void	create_child_p(t_minishell *minishell,
		t_list_cmd *curr_node, pid_t *array_pid, int i)
{
	int		error_nb;

	error_nb = 0;
	if (!is_last_node(curr_node))
		if (pipe(curr_node->pipe) < 0)
			return (free(array_pid), free_all_exit(minishell, "pipe"));
	array_pid[i] = fork();
	if (array_pid[i] == -1)
		return ;
	sig_handler_in_child();
	if (array_pid[i] == 0)
	{
		if (curr_node->size_lst != 1)
			error_nb = redirection(minishell, curr_node);
		close_fd_temp(minishell);
		if (error_nb == ERROR)
			exit_child(minishell, curr_node, 0);
		else if (error_nb == -2)
			exit_child(minishell, curr_node, 1);
		builtins_check(minishell, curr_node);
		exec_child_process(minishell, curr_node);
	}
	else
		signal_in_parent();
}

static int	exec_if_size_one(t_minishell *minishell, t_list_cmd *curr_node)
{
	int	error_nb;

	error_nb = redirection(minishell, curr_node);
	if (error_nb == ERROR)
	{
		minishell->exit_code = 1;
		return (1);
	}
	else if (error_nb == -2)
	{
		restore_std(minishell);
		g_signal_flag = 0;
		return (1);
	}
	our_builtins_exec(minishell, curr_node);
	if (our_builtins(curr_node, minishell) == 1
		|| our_builtins(curr_node, minishell) == 2
		|| (minishell->list_cmd->cmd == NULL))
	{
		restore_std(minishell);
		minishell->flag_for_export = 0;
		return (1);
	}
	return (0);
}

void	exec(t_minishell *minishell)
{
	t_list_cmd	*curr_node;
	pid_t		*array_pid;
	int			i;

	curr_node = minishell->list_cmd;
	if (minishell->list_cmd == NULL)
		return ;
	if (loop_heredoc(minishell, curr_node) == -2)
		return (restore_std(minishell), close_fd_temp(minishell));
	curr_node = minishell->list_cmd;
	if (curr_node->size_lst == 1)
		if (exec_if_size_one(minishell, curr_node) == 1)
			return (close_fd_temp(minishell));
	array_pid = ft_calloc(curr_node->size_lst + 1, sizeof(pid_t));
	if (array_pid == NULL)
		free_all_exit(minishell, "malloc");
	i = 0;
	while (curr_node)
	{
		create_child_p(minishell, curr_node, array_pid, i++);
		curr_node = curr_node->next;
	}
	parent_process(curr_node, minishell);
	waitpid_loop(minishell, array_pid);
	free(array_pid);
}
