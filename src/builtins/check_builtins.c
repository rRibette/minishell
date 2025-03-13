/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:08:35 by gougier           #+#    #+#             */
/*   Updated: 2025/03/05 13:16:02 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	our_builtins(t_list_cmd	*curr_node, t_minishell *minishell)
{
	if (curr_node->cmd == NULL)
		return (FALSE);
	if (ft_strncmp("pwd", curr_node->cmd, 4) == 0)
		return (TRUE);
	if (ft_strncmp("exit", curr_node->cmd, 5) == 0)
		return (2);
	if (ft_strncmp("cd", curr_node->cmd, 3) == 0)
		return (2);
	if (ft_strncmp("export", curr_node->cmd, 7) == 0)
	{
		if (curr_node->nb_arg == 0)
			return (TRUE);
		else if (curr_node->nb_arg > 0)
			return (minishell->flag_for_export = 1, TRUE);
	}	
	if (ft_strncmp("env", curr_node->cmd, 4) == 0)
		return (TRUE);
	if (ft_strncmp("unset", curr_node->cmd, 6) == 0)
		return (2);
	if (ft_strncmp("echo", curr_node->cmd, 5) == 0)
		return (TRUE);
	return (FALSE);
}

void	our_builtins_exec(t_minishell *minishell, t_list_cmd *curr_node)
{
	if (curr_node->cmd == NULL)
		return ;
	if (ft_strncmp("pwd", curr_node->cmd, 4) == 0)
		ft_pwd(minishell);
	if (ft_strncmp("exit", curr_node->cmd, 5) == 0)
		ft_exit(minishell, curr_node);
	if (ft_strncmp("cd", curr_node->cmd, 3) == 0)
		ft_cd(minishell, curr_node);
	if (ft_strncmp("export", curr_node->cmd, 7) == 0)
		ft_export(minishell, curr_node);
	if (ft_strncmp("env", curr_node->cmd, 4) == 0)
		ft_env(minishell, curr_node);
	if (ft_strncmp("unset", curr_node->cmd, 6) == 0)
		ft_unset(minishell, curr_node);
	if (ft_strncmp("echo", curr_node->cmd, 5) == 0)
		ft_echo(minishell, curr_node);
}
