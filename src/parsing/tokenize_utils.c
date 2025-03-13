/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rribette <rribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:39:48 by rribette          #+#    #+#             */
/*   Updated: 2025/03/06 16:12:31 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c <= 13 && c >= 9));
}

int	ft_isoperator(char *line)
{
	if (!ft_strncmp(line, "<<", 2))
		return (2);
	if (!ft_strncmp(line, "<", 1))
		return (1);
	if (!ft_strncmp(line, ">>", 2))
		return (2);
	if (!ft_strncmp(line, ">", 1))
		return (1);
	if (!ft_strncmp(line, "|", 1))
		return (1);
	return (0);
}

int	remove_quotes(char *line)
{
	int		i;
	int		j;
	char	quote;

	i = 1;
	quote = line[0];
	while (line[i] != quote)
	{
		line[i - 1] = line[i];
		i++;
	}
	i--;
	j = 1;
	while (line[i + j])
	{
		line[i + j - 1] = line[i + j + 1];
		j++;
	}
	return (i);
}

int	find_next_quote(char *line, int print)
{
	int		i;
	char	quote;

	i = 1;
	quote = line[0];
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		return (i);
	if (print)
	{	
		printf("bash: Unexpected EOF ");
		printf("while looking for matching `%c'\n", quote);
		printf("bash: syntax error : unexpected end of file\n");
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
