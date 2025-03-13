/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varsubst_itoa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rribette <rribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:29:59 by rribette          #+#    #+#             */
/*   Updated: 2025/02/13 14:21:04 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	varsubst_intlen(int nb)
{
	if (nb < 10)
		return (1);
	return (varsubst_intlen(nb / 10) + varsubst_intlen(nb % 10));
}

int	varsubst_itoa(char *line, int nb)
{
	int	len;
	int	i;

	i = 0;
	len = varsubst_intlen(nb);
	while (i < len)
	{
		line[len - 1 - i] = (nb % 10) + '0';
		nb = nb / 10;
		i++;
	}
	line[len] = 0;
	return (len);
}
