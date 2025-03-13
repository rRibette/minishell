/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:37:06 by gougier           #+#    #+#             */
/*   Updated: 2025/03/06 11:16:42 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_lst(t_env *lst)
{
	int			i;
	t_env		*current;

	if (!lst)
		return (0);
	current = lst;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

char	**put_list_to_array(void *lst)
{
	char		**array;
	t_env		*current;
	int			size;
	int			i;

	if (lst == NULL)
		return (NULL);
	size = size_lst(lst);
	current = lst;
	array = malloc(sizeof(char *) * (size + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (current)
	{
		array[i] = current->data;
		i++;
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}

t_env	*create_empty_env(t_minishell *minishell)
{
	t_env	*head;
	char	*str;

	head = NULL;
	minishell->default_param = 1;
	str = get_pwd(minishell);
	if (!str)
		return (NULL);
	head = append_node(str, head, 0);
	if (!head)
		return (NULL);
	head = append_node("SHLVL=1", head, 1);
	if (!head)
		return (NULL);
	head = append_node("_=/usr/bin/env", head, 1);
	if (!head)
		return (NULL);
	head = append_node("OLDPWD", head, 1);
	return (head);
}

t_env	*create_env(t_minishell *minishell, char **envp)
{
	t_env	*head;
	int		i;

	if (!envp || !envp[0])
		return (create_empty_env(minishell));
	head = NULL;
	i = 0;
	while (envp[i])
	{
		head = append_node(envp[i], head, 1);
		if (!head)
			return (NULL);
		i++;
	}	
	return (head);
}
