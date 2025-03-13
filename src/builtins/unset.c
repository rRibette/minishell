/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:24:45 by gougier           #+#    #+#             */
/*   Updated: 2025/02/25 12:45:01 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_minishell *minishell, t_list_cmd *curr_node)
{
	int			i;
	t_env		*existing_node;

	minishell->exit_code = 0;
	i = 1;
	if (curr_node->nb_arg == 0)
		return ;
	while (i <= curr_node->nb_arg)
	{
		existing_node = find_existing_node(minishell->env, curr_node->arg[i]);
		if (existing_node)
			minishell->env = remove_node(existing_node, minishell->env);
		i++;
	}
}
