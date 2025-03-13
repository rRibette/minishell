/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gosushi3 <gosushi3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:27:22 by gosushi3          #+#    #+#             */
/*   Updated: 2024/05/28 16:08:28 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_char;
	unsigned char	*src_char;

	if (dest == (void *) 0 && src == (void *) 0)
		return (dest);
	i = 0;
	dest_char = (unsigned char *) dest;
	src_char = (unsigned char *) src;
	if (dest_char > src_char)
	{
		while (n-- > 0)
			dest_char[n] = src_char[n];
	}
	else
	{
		while (i < n)
		{
			dest_char[i] = src_char[i];
			i++;
		}
	}
	return (dest);
}
/*#include <stdio.h>
int	main(void)
{
	char	dest[100];
	char	src[] = "salutguillaume";

	printf("%s\n", src);
	ft_memmove(dest, src, 0);
	printf("%s\n", dest);
}*/
