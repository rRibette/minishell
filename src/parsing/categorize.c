/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:37:12 by rribette          #+#    #+#             */
/*   Updated: 2025/03/08 13:42:10 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_cmdarg(t_token *token);

void	categorize_token(t_token *token)
{
	if (categorize_operator(token))
		return ;
	if (is_redirtoken(token->prev))
	{
		if (is_quoted(token->str))
			token->id = QUOTED_FILENAME;
		else
			token->id = FILENAME;
	}
	else if (is_cmdarg(token))
		token->id = CMDARG;
	else
		token->id = CMD;
}

int	categorize_operator(t_token *token)
{
	if (!ft_strncmp(token->str, "<<", 2))
		token->id = HERE_DOC;
	else if (!ft_strncmp(token->str, "<", 1))
		token->id = INREDIR;
	if (!ft_strncmp(token->str, ">>", 2))
		token->id = APPEND;
	else if (!ft_strncmp(token->str, ">", 1))
		token->id = OUTREDIR;
	if (!ft_strncmp(token->str, "|", 1))
		token->id = PIPE;
	if (is_assignment(token) && (!token->prev || token->prev->id != CMD))
	{
		if (!token->prev
			|| (token->prev->id != CMD && token->prev->id != CMDARG))
			token->id = ASSIGNMENT;
	}
	if (token->id == WORD)
		return (0);
	return (1);
}

int	is_assignment(t_token *token)
{		
	char	*line;
	int		i;

	line = token->str;
	i = 0;
	if (!ft_strchr(line, '='))
		return (0);
	while (line[i] != '=')
	{
		if (line[i] == '_')
			i++;
		else if (ft_isalnum(line[i]))
			i++;
		else
			return (0);
	}
	if (!i)
		return (0);
	if (ft_isdigit(line[0]))
		return (0);
	return (1);
}

int	is_quoted(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (find_next_quote(str + i, 1))
				return (1);
		}
		i++;
	}
	return (0);
}

static int	is_cmdarg(t_token *token)
{
	t_token	*tmp;

	tmp = token->prev;
	while (tmp)
	{
		if (tmp->id == CMD || tmp->id == CMDARG)
			return (1);
		if (tmp->id == FILENAME || is_redir_or_file(tmp))
			tmp = tmp->prev;
		else
			tmp = NULL;
	}
	return (0);
}
