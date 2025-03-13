/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:35:48 by gougier           #+#    #+#             */
/*   Updated: 2025/02/28 16:46:50 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *minishell, t_list_cmd *curr_node)
{
	t_env	*existing_node;

	if (curr_node->nb_arg > 0)
	{
		ft_putendl_fd("env: too many arguments", STDERR_FILENO);
		return ;
	}
	if (minishell->default_param != 1)
	{
		existing_node = find_existing_node(minishell->env, "PATH=");
		if (existing_node == NULL)
		{
			join_cmd_error_msg(minishell,
				"env", ": No such file or directory\n");
			minishell->exit_code = 127;
			return ;
		}
	}
	print_list_env(minishell->env);
}
