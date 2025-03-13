/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:48:21 by rribette          #+#    #+#             */
/*   Updated: 2025/03/04 19:51:11 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		add_tabs(t_token *token, t_minishell *minishell);
static t_env	*add_to_assigns(t_env *assign_tab, char *str);

void	handle_assigns(t_token *tok_list, t_minishell *minishell)
{
	t_token	*tmp;

	tmp = tok_list;
	while (tmp)
	{
		if (tmp->id != ASSIGNMENT)
			return ;
		tmp = tmp->next;
	}
	tmp = tok_list;
	while (tmp)
	{
		find_dollar(tmp->str, minishell, 0);
		if (!tmp->str)
			exit_malloc(NULL, tok_list, NULL, minishell);
		find_quotes(tmp->str);
		add_tabs(tmp, minishell);
		tmp = tmp->next;
	}
}

static void	add_tabs(t_token *token, t_minishell *minishell)
{
	t_env	*env;
	t_env	*node;

	env = minishell->env;
	node = find_existing_node(env, token->str);
	if (node)
	{
		node = change_node(node, token->str);
		if (!node)
			exit_malloc(NULL, token, NULL, minishell);
		return ;
	}
	minishell->assign_tab = add_to_assigns(minishell->assign_tab, token->str);
	if (!minishell->assign_tab)
		exit_malloc(NULL, token, NULL, minishell);
}

static t_env	*add_to_assigns(t_env *assign_tab, char *str)
{
	t_env	*node;

	node = find_existing_node(assign_tab, str);
	if (node)
	{
		node = change_node(node, str);
		if (!node)
		{
			free_list_env(assign_tab, 1);
			return (NULL);
		}
		return (assign_tab);
	}
	assign_tab = append_node(str, assign_tab, 1);
	return (assign_tab);
}
