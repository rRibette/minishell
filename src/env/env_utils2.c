/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:35:02 by rribette          #+#    #+#             */
/*   Updated: 2025/03/06 16:41:51 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*change_node(t_env *node, char *str)
{
	int	varlen;

	if (!node)
		return (NULL);
	if (!str)
		return (node);
	varlen = var_len(str);
	if (!str[varlen])
		return (node);
	free(node->data);
	free(node->var);
	free(node->subst);
	node->data = ft_strdup(str);
	node->var = ft_strldup(str, varlen);
	node->subst = ft_strdup(str + varlen + 1);
	if (!node->data || !node->var || !node->subst)
		return (NULL);
	return (node);
}

t_env	*remove_node(t_env *node, t_env *head)
{
	t_env	*tmp;

	if (!head || !node)
		return (head);
	if (!node->next && !node->prev)
	{
		free_node(node, 1);
		return (NULL);
	}
	else if (!node->next)
		node->prev->next = NULL;
	else if (!node->prev)
	{
		node->next->prev = NULL;
		tmp = node->next;
		free_node(node, 1);
		return (tmp);
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	free_node(node, 1);
	return (head);
}

void	print_node(t_env *node)
{
	if (!node)
	{
		printf("empty node\n");
		return ;
	}
	printf("%s \n%s\t=\t%s\n", node->data, node->var, node->subst);
}

void	print_env(t_env *env)
{
	t_env	*node;

	node = env;
	while (node)
	{
		print_node(node);
		node = node->next;
	}
}
