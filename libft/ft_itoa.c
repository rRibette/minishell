/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:24:44 by gougier           #+#    #+#             */
/*   Updated: 2024/05/28 13:57:35 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_nb(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		i;
	int		len;
	long	nb;

	nb = n;
	len = ft_len_nb(n);
	i = len - 1;
	dest = malloc (sizeof (char) * len + 1);
	if (dest == NULL)
		return (NULL);
	if (nb < 0)
	{
		nb *= -1;
		dest[0] = '-';
	}
	while (nb > 9)
	{
		dest[i--] = nb % 10 + '0';
		nb = nb / 10;
	}
	dest[i] = nb + '0';
	dest[len] = '\0';
	return (dest);
}
/*#include <stdio.h>
int	main(void)
{
	char *str;
	str = ft_itoa(-2147483647);
	printf("%s", str);
	free(str);
}*/
