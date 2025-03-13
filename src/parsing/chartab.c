/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chartab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:57:03 by rribette          #+#    #+#             */
/*   Updated: 2025/03/06 17:46:01 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**chartab_init(int len)
{
	char	**res;
	int		i;

	res = malloc((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len + 1)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

char	**free_chartab(char **chartab)
{
	int	i;

	i = 0;
	if (!chartab)
		return (NULL);
	while (chartab[i])
	{
		free(chartab[i]);
		i++;
	}
	free(chartab);
	return (NULL);
}

int	chartab_len(char **chartab)
{
	int	len;

	len = 0;
	while (chartab[len])
		len++;
	return (len);
}

char	**chartab_merge(char **tab1, char **tab2, int index)
{
	int		totlen;
	int		len2;
	char	**res;
	int		i;

	if (!tab1 || !tab2)
		return (tab1);
	len2 = chartab_len(tab2);
	totlen = len2 + chartab_len(tab1);
	res = malloc((totlen + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < totlen)
	{
		if (i < index)
			res[i] = tab1[i];
		else if (i < index + len2)
			res[i] = tab2[i - index];
		else
			res[i] = tab1[i - len2];
		i++;
	}
	res[i] = 0;
	return (res);
}

//does not realloc the table (simply rearranges the lines)
//does not free the deleted line but returns it

char	*del_line(char **tab, int index)
{
	int		i;
	char	*res;

	i = index;
	res = tab[i];
	while (tab[i + 1])
	{
		tab[i] = tab[i + 1];
		i++;
	}
	tab[i] = 0;
	return (res);
}
