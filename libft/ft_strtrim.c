/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:43:30 by gougier           #+#    #+#             */
/*   Updated: 2024/06/06 13:34:17 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	ft_countsep1(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && set[j])
	{
		j = 0;
		while (set[j] && s1[i] != set[j])
			j++;
		if (s1[i] == set[j])
			i++;
	}
	return (i);
}

static int	ft_countsep2(char const *s1, char const *set)
{
	int			i;
	const char	*temp;
	int			j;

	temp = s1;
	i = 0;
	j = 0;
	while (s1[i])
		i++;
	i--;
	if (i < 0)
		return (0);
	while (&s1[i] != temp && set[j])
	{
		j = 0;
		while (set[j] && s1[i] != set[j])
			j++;
		if (s1[i] == set[j])
			i--;
	}
	i++;
	return (fft_strlen(s1) - (i));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		k;
	int		j;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	j = 0;
	i = ft_countsep1(s1, set);
	k = ft_countsep2(s1, set);
	if (fft_strlen(s1) - (i + k) < 0)
	{
		s1 = "";
		i = 0;
		k = 0;
	}
	dest = malloc (sizeof (char) * (fft_strlen(s1) - (i + k)) + 1);
	if (dest == NULL)
		return (NULL);
	while (j < (fft_strlen(s1) - (i + k)))
	{
		dest [j] = s1[i + j];
		j++;
	}
	return (dest[j] = '\0', dest);
}
/*#include <stdio.h>
int	main()
{
	const char *s1 = "";
	const char *set = "";
	printf("%s\n", ft_strtrim(s1, set));
}*/
