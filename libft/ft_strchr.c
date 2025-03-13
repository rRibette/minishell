/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:16:41 by gougier           #+#    #+#             */
/*   Updated: 2024/06/18 13:36:07 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	cpy;
	char			*new;

	cpy = c;
	new = (char *)s;
	while (*new)
	{
		if (*new == cpy)
			return (new);
		new++;
	}
	if (*new == cpy)
		return (new);
	return (NULL);
}

/*#include <stdio.h>
int	main(void)
{
	const char	str[] = "salutation";
	const char ch = 'a';
	char *ret;

	ret = ft_strchr(str, ch);
	printf("%s", ret);
}*/
