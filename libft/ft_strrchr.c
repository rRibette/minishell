/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:48:41 by gougier           #+#    #+#             */
/*   Updated: 2024/06/18 13:37:44 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	cpy;
	char			*new;
	char			*debut;

	cpy = c;
	new = (char *)s;
	debut = new;
	while (*new)
		new++;
	while (new != debut)
	{
		if (*new == cpy)
			return (new);
		new--;
	}
	if (*new == cpy)
		return (new);
	return (NULL);
}
/*#include <stdio.h>
int	main(void)
{
	const char      str[] = "salutation";
        const char ch = 'a';
        char *ret;
        ret = ft_strrchr(str, ch);
        printf("%s", ret);
}*/
