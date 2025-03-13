/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varsubst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:26:21 by rribette          #+#    #+#             */
/*   Updated: 2025/03/06 14:57:09 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_varcmp(char *env_var, char *var)
{
	int	i;

	i = 0;
	while (env_var[i] && env_var[i] == var[i])
		i++;
	if (var[i] == '=')
		return (0);
	return (env_var[i] - var[i]);
}

int	dollar_type(char *line)
{
	int	i;

	i = 0;
	if (line[i] && ft_isalnum(line[i + 1]))
		i++;
	if (line[1] == '?')
		return (-1);
	while (ft_isalnum(line[i]))
		i++;
	return (i);
}

char	*create_special_dollar(char *line, int idx, int len, t_minishell *mish)
{
	int		exit_code;
	int		totlen;
	int		varlen;
	char	*newline;

	if (len == -1)
	{
		exit_code = mish->exit_code;
		varlen = varsubst_intlen(exit_code);
		totlen = ft_strlen(line) - 2 + varlen;
		newline = cpy_special_dollar(line, idx, totlen, exit_code);
	}
	else
		newline = NULL;
	return (newline);
}

char	*cpy_special_dollar(char *line, int idx, int totlen, int exit_code)
{
	char	*newline;
	int		i;
	int		j;

	newline = malloc((totlen + 1) * sizeof(char));
	if (!newline)
		return (NULL);
	i = 0;
	j = 0;
	while (i + j < totlen)
	{
		if (i + j == idx)
			j = varsubst_itoa(newline + i + j, exit_code);
		else
		{
			if (i < idx)
				newline[i + j] = line[i];
			else
				newline[i + j] = line[i + 2];
			i++;
		}
	}
	return (newline);
}
