/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gosushi3 <gosushi3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:59:35 by gosushi3          #+#    #+#             */
/*   Updated: 2024/05/27 11:39:29 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

/*int	main(void)
{
	int	result;
	int	result2;

	result = ft_isprint('	');
	result2 = isprint('	');
	printf("%d\n", result);
	printf("%d\n", result2);
}*/
