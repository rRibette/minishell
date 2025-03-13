/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:04:01 by rribette          #+#    #+#             */
/*   Updated: 2025/03/06 16:43:53 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *var, int dup)
{
	t_env	*node;
	int		varlen;

	if (!var)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->data = NULL;
	node->var = NULL;
	node->subst = NULL;
	node->next = NULL;
	node->prev = NULL;
	varlen = var_len(var);
	if (!dup)
		node->data = var;
	else
		node->data = ft_strdup(var);
	node->var = ft_strldup(var, varlen);
	if (var[varlen] == '=')
		node->subst = ft_strdup(var + varlen + 1);
	else
		node->subst = ft_strdup(var + varlen);
	return (check_node(node, dup));
}

int	var_len(char *var)
{
	int	len;

	len = 0;
	if (!var)
		return (-1);
	while (var[len] && var[len] != '=')
		len++;
	return (len);
}

t_env	*check_node(t_env *node, int dup)
{
	if (node->data && node->var && node->subst)
		return (node);
	free_node(node, dup);
	return (NULL);
}

void	free_node(t_env *node, int dup)
{
	if (node->data && dup)
		free(node->data);
	if (node->var)
		free(node->var);
	if (node->subst)
		free(node->subst);
	free(node);
}

t_env	*append_node(char *node_str, t_env *head, int dup)
{
	t_env	*node;
	t_env	*tmp;

	node = create_env_node(node_str, dup);
	if (!node)
	{
		free_list_env(head, dup);
		return (NULL);
	}
	tmp = head;
	node->index = 0;
	if (!head)
		return (node);
	while (tmp->next)
	{
		node->index++;
		tmp = tmp->next;
	}
	node->prev = tmp;
	tmp->next = node;
	return (head);
}
