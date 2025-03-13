/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdarg_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:00:37 by rribette          #+#    #+#             */
/*   Updated: 2025/03/06 17:42:53 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**cmdargs_split(char *line)
{
	int		nb_word;
	char	**res;
	int		i;
	int		cnt;
	int		test;

	nb_word = cmdarg_cw(line);
	res = chartab_init(nb_word);
	if (!res)
		return (NULL);
	cnt = 0;
	i = 0;
	while (cnt < nb_word)
	{
		i += skip_spaces(line + i);
		test = append_word(line + i, res, cnt);
		if (test == -1)
			return (NULL);
		i += test;
		cnt++;
	}
	return (res);
}

int	cmdarg_cw(char *line)
{
	int	i;
	int	cnt;
	int	word;

	i = 0;
	cnt = 0;
	word = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			i += find_next_quote(line + i, 0);
		if (ft_isspace(line[i]))
		{
			word = 0;
			i += skip_spaces(line + i);
		}
		else
		{
			if (!word)
				cnt++;
			word = 1;
			i++;
		}
	}
	return (cnt);
}

int	append_word(char *line, char **table, int index)
{
	int		len;
	int		i;
	char	*res;

	len = cmd_len(line);
	i = 0;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
	{
		free_chartab(table);
		return (-1);
	}
	while (i < len)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = 0;
	table[index] = res;
	return (len);
}

int	cmd_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && !ft_isspace(line[len]))
	{
		if (line[len] == 34 || line[len] == 39)
			len += find_next_quote(line + len, 0);
		len++;
	}
	return (len);
}
