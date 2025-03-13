/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:18:29 by gougier           #+#    #+#             */
/*   Updated: 2024/05/27 11:32:09 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*big_2;
	char	*little_2;
	size_t	i;
	size_t	j;

	big_2 = (char *)big;
	little_2 = (char *)little;
	i = 0;
	if (*little_2 == '\0')
		return (big_2);
	while (big_2[i] && i < len)
	{
		j = 0;
		if (big_2[i] == little_2[j])
		{
			while (big_2[i + j] == little_2[j] && ((i + j) < len))
			{
				if (little_2[j + 1] == '\0')
					return (&big_2[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
int	main(void)
{
	const char *big = "Foo Bar Baz";
	const char *little = "z";
	char *ptr;
	ptr = ft_strnstr(big, little, 12);
	printf("%s", ptr);
}*/
