/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:02:00 by gougier           #+#    #+#             */
/*   Updated: 2024/05/27 16:52:05 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n >= 0 && n <= 9)
		ft_putchar_fd((n + '0'), fd);
	else if (n < 0)
	{
		if (n == -2147483648)
		{
			write (fd, "-2147483648", 11);
		}
		else
		{
			ft_putchar_fd('-', fd);
			ft_putnbr_fd(n *(-1), fd);
		}
	}
	else
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
}
/*#include <stdio.h>
int main ()
{
	int	text = 0;
	int nbr2 = -3546355;
	ft_putnbr_fd(nbr2, text);
}*/
