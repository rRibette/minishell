/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:52:35 by gougier           #+#    #+#             */
/*   Updated: 2024/06/05 19:13:47 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_char;
	unsigned char	cpy;
	size_t			i;

	i = 0;
	s_char = (unsigned char *)s;
	cpy = c;
	if (n == 0)
		return (NULL);
	if (s_char[i] == cpy)
		return (&s_char[i]);
	while (i < n && *s_char != cpy)
	{
		if (s_char[i] == cpy)
			return (&s_char[i]);
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
int main(void)
{
	char data[] = {10};
	const unsigned int size = 0;
	void *found = ft_memchr( data, 10, size);
	printf("%s\n", (found != NULL ? "found" : "not found"));
}*/
