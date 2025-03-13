/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:35:05 by gougier           #+#    #+#             */
/*   Updated: 2025/03/11 12:27:16 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_shlvl(t_minishell *minishell, t_list_cmd *curr_node)
{
	if (ft_strncmp("./minishell", curr_node->cmd, 12) == 0)
		update_shlvl(minishell, "SHLVL=");
}

static int	get_shlvl(t_env *node)
{
	int		i;
	char	*nb_from_shlvl;

	i = 0;
	if (ft_strchr(node->data, '=') == NULL)
		return (1);
	while (node->data[i] && node->data[i] != '=')
		i++;
	if (node->data[i] == '=')
		i++;
	nb_from_shlvl = node->data + i;
	return (ft_atoi(nb_from_shlvl));
}

void	update_shlvl(t_minishell *minishell, char *str)
{
	t_env	*existing_node;
	char	*shlvl_nb;
	int		shlvl;

	existing_node = find_existing_node(minishell->env, str);
	if (existing_node)
	{
		shlvl = (get_shlvl(existing_node) + 1);
		shlvl_nb = ft_itoa(shlvl);
		if (shlvl_nb == NULL)
			free_all_exit(minishell, "malloc");
		free(existing_node->data);
		existing_node->data = ft_strjoin(str, shlvl_nb);
		if (existing_node->data == NULL)
			free_all_exit(minishell, "malloc");
		return ;
	}
	minishell->env = append_node(ft_strjoin(str, "0"), minishell->env, 0);
	if (minishell->env == NULL)
		free_all_exit(minishell, "malloc");
}
