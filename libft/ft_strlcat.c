/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:05:17 by gougier           #+#    #+#             */
/*   Updated: 2024/05/28 17:06:26 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*#include <bsd/string.h>*/

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j] && ((j + i + 1) < siz))
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[j + i] = '\0';
	if (siz < i)
		return (ft_strlen(src) + siz);
	else
		return (ft_strlen(src) + i);
}
/*#include <stdio.h>
int	main(void)
{
	char	dst[10] = "sa";
	char	dst_2[10] = "sa";
	char	*src = "gui";
	printf("%zd\n", ft_strlcat(dst, src, 5));
	printf("%zd\n", strlcat(dst_2, src, 5));
}*/
