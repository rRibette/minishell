/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:34:30 by gougier           #+#    #+#             */
/*   Updated: 2025/03/06 11:38:13 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_char;
	unsigned char	*s2_char;
	size_t			i;

	s1_char = (unsigned char *)s1;
	s2_char = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && i + 1 < n)
	{
		if (s1_char[i] != s2_char[i])
			return (s1_char[i] - s2_char[i]);
		i++;
	}
	return (s1_char[i] - s2_char[i]);
}
/*#include <stdio.h>
int	main(void)
{
	const char *s1 = "salutation";
	const char *s2 = "salut";
	printf("%d", ft_strncmp(s1, s2, 4));
}*/
