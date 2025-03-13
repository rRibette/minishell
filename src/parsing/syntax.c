/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:10:47 by rribette          #+#    #+#             */
/*   Updated: 2025/03/06 10:20:27 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_pipe_syntax(t_token *token, char *line, t_token *list);
static int	check_redir_syntax(t_token *token, char *line, t_token *list);
static int	syntax_error(t_token *list, char *line, t_token *token);

int	check_syntax(t_token *list, char *line)
{
	t_token	*tmp;
	int		test;

	tmp = list;
	test = 0;
	while (tmp)
	{
		if (tmp->id == PIPE)
			test = check_pipe_syntax(tmp, line, list);
		else if (is_redirtoken(tmp))
			test = check_redir_syntax(tmp, line, list);
		if (test)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	check_pipe_syntax(t_token *token, char *line, t_token *list)
{
	if (token->prev == NULL)
		return (syntax_error(list, line, token));
	if (token->next == NULL)
		return (syntax_error(list, line, NULL));
	return (0);
}

static int	check_redir_syntax(t_token *token, char *line, t_token *list)
{
	if (token->next && token->next->id == FILENAME)
		return (0);
	if (token->next && token->next->id == QUOTED_FILENAME)
		return (0);
	return (syntax_error(list, line, token->next));
}

static int	syntax_error(t_token *list, char *line, t_token *token)
{
	t_token	*tmp;

	free(line);
	printf("syntax error near token : ");
	if (token)
		printf("%s\n", token->str);
	else
		printf("newline\n");
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->str);
		free(tmp);
	}
	return (1);
}
