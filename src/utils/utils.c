/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 08:17:25 by gougier           #+#    #+#             */
/*   Updated: 2025/02/24 10:38:28 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strndup(char *s, int n)
{
	char	*dest;

	dest = malloc (sizeof(char) * (n + 1));
	if (dest == NULL)
		return (NULL);
	ft_strcpy(dest, s);
	return (dest);
}

long	ft_atol(char *s)
{
	int		i;
	long	nb;
	int		sign;

	nb = 0;
	i = 0;
	sign = 1;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		nb = nb * 10 + (s[i] - '0');
		i++;
	}
	return (nb * sign);
}

int	is_first_node(t_list_cmd *lst)
{
	if (lst)
	{
		if (lst->index == 0)
			return (1);
	}
	return (0);
}

int	is_last_node(t_list_cmd *lst)
{
	if (lst)
	{
		if (lst->index == lst->size_lst - 1)
			return (1);
	}
	return (0);
}
