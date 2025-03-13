/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gosushi3 <gosushi3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:33:33 by gosushi3          #+#    #+#             */
/*   Updated: 2024/05/27 11:40:17 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_char;
	unsigned char	*src_char;

	if (dest == (void *) 0 && src == (void *) 0)
		return (dest);
	i = 0;
	dest_char = (unsigned char *) dest;
	src_char = (unsigned char *) src;
	while (i < n)
	{
		*dest_char = *src_char;
		dest_char++;
		src_char++;
		i++;
	}
	return (dest);
}

/*int	main(void)
{
	char	src[] = "guillaume";
	char 	dest[50];

	printf("%s\n",src);
	ft_memcpy(dest, src, 9);
	printf("%s\n",dest);
}*/
