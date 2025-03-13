/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gosushi3 <gosushi3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:49:59 by gosushi3          #+#    #+#             */
/*   Updated: 2024/05/27 11:37:48 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dest;

	dest = (unsigned char *) s;
	while (n > 0)
	{
		*dest = '\0';
		dest++;
		n--;
	}
}

/*int	main(void)
{
	char	str[10];

	strcpy(str, "salutgui");
	printf("%s\n", str);
	ft_bzero(str, 5);
	printf("%s\n", str);
}*/
