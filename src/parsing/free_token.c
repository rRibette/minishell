/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rribette <rribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:03:51 by rribette          #+#    #+#             */
/*   Updated: 2025/03/04 19:12:22 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	full_free_test(t_tokid id);

t_token	*return_tokenize(char *line, t_token *list, t_token *token)
{
	if (line)
		free(line);
	if (token)
		free(token);
	free_token_list(list, 0);
	return (NULL);
}

void	free_token_list(t_token *list, int str_keep)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (!str_keep && tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

void	exit_malloc(char *line, t_token *list, t_token *token, t_minishell *msh)
{
	if (line)
		free(line);
	free_token_list(list, 0);
	free_token_list(token, 0);
	free_all_exit(msh, NULL);
}

void	full_free_token(t_token *list)
{
	t_token	*token;
	t_tokid	id;

	token = list;
	while (list)
	{
		token = list;
		list = list->next;
		id = token->id;
		if (!full_free_test(id))
			free(token->str);
		free(token);
	}
}

static int	full_free_test(t_tokid id)
{
	if (id == CMD || id == CMDARG)
		return (1);
	if (id == FILENAME || id == QUOTED_FILENAME)
		return (1);
	return (0);
}
