/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:37:13 by gougier           #+#    #+#             */
/*   Updated: 2024/05/29 12:32:28 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*dest;
	int				i;

	i = 0;
	if (nmemb != 0 || size != 0)
	{
		if (nmemb > INT_MAX || size > INT_MAX || nmemb * size > INT_MAX)
			return (NULL);
	}
	dest = malloc (nmemb * size);
	if (dest == NULL)
		return (NULL);
	while ((nmemb * size) - i > 0)
		dest[i++] = '\0';
	return (dest);
}
/*
#include <stdio.h>

int main () {
	char	*a;

	a = ft_calloc(1, 0);
	if (!(*a))
		printf("%s\n%p\n", a, a);
	free( a );

   return(0);
}
*/
