/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 09:24:01 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 13:00:16 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_bad_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(*str))
		return (1);
	if (str[i] == '=')
		return (1);
	while (str[i] != '=' && str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

t_env	*find_existing_node(t_env *env, char *str)
{
	t_env	*curr_node;

	if (env == NULL)
		return (NULL);
	curr_node = env;
	while (curr_node)
	{
		if (ft_varcmp(curr_node->var, str) == 0)
			return (curr_node);
		curr_node = curr_node->next;
	}
	return (NULL);
}

static void	append_or_replace(t_minishell *minishell, char *str)
{
	t_env	*existing_node;

	existing_node = find_existing_node(minishell->env, str);
	if (existing_node)
	{
		if (!change_node(existing_node, str))
			free_all_exit(minishell, "malloc");
		return ;
	}
	minishell->env = append_node(str, minishell->env, 1);
	if (!minishell->env)
		free_all_exit(minishell, "malloc");
}

void	final_export(t_minishell *minishell, char *str)
{
	if (check_bad_identifier(str) == 1)
	{
		export_error_msg(str, minishell);
		minishell->exit_code = 1;
		if (minishell->flag_for_export == 1)
			return ;
	}
	else
		append_or_replace(minishell, str);
}

void	export_with_arg(t_minishell *minishell, t_list_cmd *curr_node)
{
	int			i;

	i = 1;
	while (curr_node->arg[i] != NULL)
	{
		final_export(minishell, curr_node->arg[i]);
		i++;
	}
}
