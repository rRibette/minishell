/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:13:48 by gougier           #+#    #+#             */
/*   Updated: 2024/05/29 13:05:21 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_size(char const *s, unsigned int start, size_t len)
{
	if (start > ft_strlen(s))
		return (0);
	else if (len < (ft_strlen(s) - start))
		return (len);
	else
		return (ft_strlen(s) - start);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	size;

	size = ft_size(s, start, len);
	i = 0;
	dest = malloc (sizeof (char) * size + 1);
	if (dest == NULL)
		return (NULL);
	while (start < ft_strlen(s) && s[start] && size-- > 0)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char *s = "hola";
	printf("%s", ft_substr(s, 4294967295, 0));
}
*/
