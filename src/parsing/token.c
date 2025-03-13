/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:26:49 by rribette          #+#    #+#             */
/*   Updated: 2025/03/13 13:46:48 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

t_token	*append_token(t_token *list, t_token *token, char *l, t_minishell *mish)
{
	t_token	*tmp;

	(void)mish;
	if (!token)
		return (list);
	if (list)
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		token->prev = tmp;
		tmp->next = token;
	}
	token->str = ft_strldup(token->str, token->toklen);
	if (!token->str)
		exit_malloc(l, list, token, mish);
	categorize_token(token);
	if (!list)
		return (token);
	return (list);
}
/*
void	print_token(t_token *token)
{
	while (token)
	{
		printf("token : %s, ", token->str);
		if (token->id == WORD)
			printf("ID = WORD\n");
		if (token->id == CMD)
			printf("ID = CMD\n");
		if (token->id == CMDARG)
			printf("ID = CMDARG\n");
		if (token->id == PIPE)
			printf("ID = PIPE\n");
		if (token->id == HERE_DOC)
			printf("ID = HERE_DOC\n");
		if (token->id == APPEND)
			printf("ID = APPEND\n");
		if (token->id == OUTREDIR)
			printf("ID = OUTREDIR\n");
		if (token->id == INREDIR)
			printf("ID = INREDIR\n");
		if (token->id == FILENAME)
			printf("ID = FILENAME\n");
		if (token->id == QUOTED_FILENAME)
			printf("ID = QUOTED_FILENAME\n");
		if (token->id == ASSIGNMENT)
			printf("ID = ASSIGNMENT\n");
		token = token->next;
	}
}
*/

t_token	*create_token(char *line)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->id = WORD;
	token->str = line;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}
