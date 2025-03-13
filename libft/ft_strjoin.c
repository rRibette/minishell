/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:06:09 by gougier           #+#    #+#             */
/*   Updated: 2024/07/02 13:01:24 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	i = 0;
	j = 0;
	dest = malloc (sizeof (char) * (s1_len + ft_strlen(s2)) + 1);
	if (dest == NULL)
		return (NULL);
	while (i < s1_len)
	{
		dest[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		dest[i + j] = s2[j];
		j++;
	}
	return ((dest[i + j] = '\0'), dest);
}
/*#include <stdio.h>
int	main(void)
{
	char *s1 = "salut";
	char *s2 = "guillaume";
	printf("%s",ft_strjoin(s1, s2));
}*/
