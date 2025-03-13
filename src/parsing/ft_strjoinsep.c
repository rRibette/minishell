/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinsep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:37:42 by rribette          #+#    #+#             */
/*   Updated: 2025/02/26 15:20:06 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strjoinsep(char *str1, char *str2, char sep)
{
	int		len;
	char	*res;
	int		i;

	len = ft_strlen(str1) + ft_strlen(str2) + 1;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	len = ft_strlen(str1);
	i = 0;
	while (i < len)
	{
		res[i] = str1[i];
		i++;
	}
	res[i] = sep;
	i++;
	while (str2[i - (len + 1)])
	{
		res[i] = str2[i - (len + 1)];
		i++;
	}
	res[i] = 0;
	return (res);
}
