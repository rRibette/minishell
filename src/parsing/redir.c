/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rribette <rribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:13:03 by rribette          #+#    #+#             */
/*   Updated: 2025/03/08 10:20:46 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_redir	*get_redir(t_token *list, t_minishell *mish)
{
	t_token	*tmp;
	t_redir	*redir_list;
	t_redir	*redir_node;

	tmp = list;
	redir_list = NULL;
	while (tmp && tmp->id != PIPE)
	{
		if (is_redir(tmp))
		{
			redir_node = init_redir_node(tmp->next->str, mish);
			if (!redir_node)
				return (NULL);
			redir_node->filemode = get_filemode(tmp->id);
			if (tmp->next->id == QUOTED_FILENAME)
				redir_node->quoted = 1;
			redir_list = append_redir(redir_list, redir_node);
		}
		tmp = tmp->next;
	}
	return (redir_list);
}

int	get_filemode(t_tokid id)
{
	if (id == HERE_DOC)
		return (0);
	if (id == INREDIR)
		return (1);
	if (id == APPEND)
		return (2);
	if (id == OUTREDIR)
		return (3);
	return (-1);
}

t_redir	*init_redir_node(char *str, t_minishell *minishell)
{
	t_redir	*node;
	char	*new_str;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	new_str = find_dollar(str, minishell, 0);
	if (!new_str)
	{
		free(node);
		return (NULL);
	}
	find_quotes(new_str);
	node->filemode = -1;
	node->quoted = 2;
	node->filename = new_str;
	node->next = NULL;
	return (node);
}

t_redir	*append_redir(t_redir *redir_list, t_redir *redir_node)
{
	t_redir	*tmp;

	if (!redir_node)
		return (redir_list);
	if (!redir_list)
		return (redir_node);
	tmp = redir_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir_node;
	return (redir_list);
}

int	is_redir(t_token *token)
{
	if (!token->next)
		return (0);
	return (token->next->id == FILENAME || token->next->id == QUOTED_FILENAME);
}
