/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:23:45 by gougier           #+#    #+#             */
/*   Updated: 2025/02/28 16:46:11 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_path_case(t_minishell *minishell, t_list_cmd *curr_node)
{
	join_cmd_error_msg(minishell,
		curr_node->cmd, ": No such file or directory\n");
	minishell->flag_no_path = 0;
	minishell->exit_code = 127;
	free_all_exit(minishell, NULL);
}

int	file_exist(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
		return (1);
	return (0);
}

void	execve_fail(t_minishell *minishell, char *path)
{
	error_msg(minishell, path);
	minishell->exit_code = 127;
	free_all_exit(minishell, NULL);
}

void	join_cmd_error_msg(t_minishell *minishell, char *cmd, char *error)
{
	char	*temp;

	temp = NULL;
	if (cmd)
	{
		temp = ft_strjoin(cmd, error);
		if (temp == NULL)
			free_all_exit(minishell, "malloc");
		else
			ft_putstr_fd(temp, STDERR_FILENO);
		free(temp);
	}
	else
		ft_putstr_fd(error, STDERR_FILENO);
}
