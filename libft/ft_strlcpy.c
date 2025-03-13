/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:03:02 by gougier           #+#    #+#             */
/*   Updated: 2024/05/28 13:28:59 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	int	i;

	i = 0;
	if (siz == 0)
		return (ft_strlen(src));
	while (src[i] && (siz - 1) > 0)
	{
		dst[i] = src[i];
		i++;
		siz--;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*#include <stdio.h>
int	main(void)
{
	char	*src = "sfgdfhdfgdgal";
	char	dst[10];

	printf("%zd\n", ft_strlcpy(dst, src, 10));
	printf("%s", dst);
}*/
