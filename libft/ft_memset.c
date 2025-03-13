/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gosushi3 <gosushi3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:24:46 by gosushi3          #+#    #+#             */
/*   Updated: 2024/05/27 11:40:59 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	cpy;

	dest = (unsigned char *) s;
	cpy = c;
	while (n > 0)
	{
		*dest = cpy;
		dest++;
		n--;
	}
	return (s);
}

/*int	main(void)
{
	char	str[20];
	
	strcpy(str, "salut guillaume");
	printf("str avant fonction : %s\n", str);
	ft_memset(str, 'A', 5);
	printf("str apres fonction : %s\n", str);
}*/
