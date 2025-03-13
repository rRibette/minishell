/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:29:00 by gougier           #+#    #+#             */
/*   Updated: 2025/03/06 11:38:28 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	char	*s1;

	s1 = (char *)s;
	dest = malloc (sizeof(char) * ft_strlen(s1) + 1);
	if (dest == NULL)
		return (0);
	ft_strcpy(dest, s1);
	return (dest);
}
/*#include <stdio.h>
int	main(void)
{
	char	str[] = "guillaume";
	char	*dup;
	dup = ft_strdup(str);
	printf("%s", dup);
	free(dup);
}*/
