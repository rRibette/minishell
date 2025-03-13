/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:20:45 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 13:40:06 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list_cmd	*parse(char *line, t_minishell *minishell)
{
	t_token		*tokens;
	t_list_cmd	*parsing;

	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	tokens = tokenize(line, minishell);
	if (!tokens)
		return (NULL);
	if (check_syntax(tokens, line))
	{
		minishell->exit_code = 2;
		return (NULL);
	}
	handle_assigns(tokens, minishell);
	parsing = fill_parsing(tokens, line, minishell);
	get_lst_size(parsing);
	full_free_token(tokens);
	return (parsing);
}

t_list_cmd	*fill_parsing(t_token *list, char *line, t_minishell *mish)
{
	t_list_cmd	*parsing;
	t_list_cmd	*head;

	parsing = init_list_cmd(line, list, 0, mish);
	head = parsing;
	if (!parsing)
		return (NULL);
	while (list)
	{
		if (list->id == CMD)
			list = get_cmdargs(parsing, list, mish);
		if (list->id == PIPE)
			parsing = app_p(head, line, list->next, mish);
		list = list->next;
	}
	return (head);
}

t_list_cmd	*init_list_cmd(char *l, t_token *lst, int i, t_minishell *mish)
{
	t_list_cmd	*res;

	if (!l)
		return (NULL);
	res = malloc(sizeof(t_list_cmd));
	if (!res)
		return (NULL);
	res->input = l;
	res->arg = NULL;
	res->cmd = NULL;
	res->nb_arg = 0;
	res->index = i;
	res->heredoc_file = NULL;
	res->redir_list = get_redir(lst, mish);
	res->pipe[0] = -1;
	res->pipe[1] = -1;
	res->next = NULL;
	return (res);
}

t_list_cmd	*app_p(t_list_cmd *p, char *l, t_token *lst, t_minishell *msh)
{
	t_list_cmd	*new_node;
	t_list_cmd	*tmp;
	int			i;

	i = 0;
	tmp = p;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	new_node = init_list_cmd(l, lst, i + 1, msh);
	if (!new_node)
		return (return_free_parsing(p));
	tmp->next = new_node;
	new_node->prev = tmp;
	return (new_node);
}

void	get_lst_size(t_list_cmd *list)
{
	int			lst_size;
	t_list_cmd	*tmp;

	tmp = list;
	if (!list)
		return ;
	lst_size = 0;
	while (tmp)
	{
		lst_size++;
		tmp = tmp->next;
	}
	tmp = list;
	while (tmp)
	{
		tmp->size_lst = lst_size;
		tmp = tmp->next;
	}
}
