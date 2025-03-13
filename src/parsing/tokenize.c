/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:20:45 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 12:56:15 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

t_token	*tokenize(char *line, t_minishell *minishell)
{
	int		i;
	int		toklen;
	t_token	*list;
	t_token	*token;

	i = 0;
	list = NULL;
	if (!line)
		return (NULL);
	while (line[i])
	{
		i += skip_spaces(line + i);
		token = create_token(line + i);
		if (!token)
			exit_malloc(line, list, NULL, minishell);
		toklen = find_eotok(line + i);
		if (!toklen)
			return (return_tokenize(line, list, token));
		i += toklen;
		token->toklen = toklen;
		list = append_token(list, token, line, minishell);
		i += skip_spaces(line + i);
	}
	return (list);
}

int	find_eotok(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39 || line[i] == 34)
		{
			j = find_next_quote(line + i, 1);
			if (!j)
				return (0);
			i += j;
		}
		else if (ft_isoperator(line + i))
		{
			if (i)
				return (i);
			return (ft_isoperator(line));
		}
		else if (ft_isspace(line[i]))
			return (i);
		i++;
	}
	return (i);
}

char	*find_dollar(char *line, t_minishell *minishell, int quoted)
{
	int		i;
	char	*res;

	i = 0;
	if (quoted == 1)
		return (line);
	while (line[i])
	{
		if (line[i] == 39 && !quoted)
			i += find_next_quote(line + i, 1) + 1;
		else if (line[i] == '$')
		{
			res = replace_dollar(line, i, minishell);
			free(line);
			if (!res)
				return (NULL);
			line = res;
			if (line[i] == '$')
				i++;
		}
		else
			i++;
	}
	return (line);
}

void	find_quotes(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			if (find_next_quote(line + i, 1))
				i += remove_quotes(line + i);
		}
		else
			i++;
	}
}

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}
