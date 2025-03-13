/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:00:14 by gougier           #+#    #+#             */
/*   Updated: 2025/01/10 12:23:56 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_count(const char *s, char c)
{
	int		i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\0')
			return (count);
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_cpy(char *dest, const char *s, size_t word_len, size_t k)
{
	size_t	i;

	i = 0;
	while (i < word_len)
	{
		dest[i] = s[i + k];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**ft_dup(char **dest, const char *s, char c, size_t nb_word)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	word_len;

	i = 0;
	j = 0;
	word_len = 0;
	while (s[i] && j < nb_word)
	{
		while (s[i] && s[i] == c)
			i++;
		k = i;
		while (s[i] && s[i++] != c)
			word_len++;
		dest[j] = malloc (word_len + 1);
		if (dest[j] == NULL)
			return (ft_free(dest));
		ft_cpy(dest[j], s, word_len, k);
		word_len = 0;
		j++;
	}
	dest[j] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	size_t	nb_word;
	char	**dest;

	if (!s)
		return (NULL);
	nb_word = ft_count(s, c);
	dest = malloc (sizeof (char *) * (nb_word + 1));
	if (dest == NULL)
		return (NULL);
	dest[nb_word] = NULL;
	if (!ft_dup(dest, s, c, nb_word))
		return (NULL);
	return (dest);
}

/*#include <stdio.h>
int		main(void)
{
	int i = 0;
	char **tab;
	char c = ' ';

	tab = ft_split("bonjour je mappelle guillaume", c);
	while (i < 4)
	{
		printf("string %d : %s\n", i, tab[i]);
		i++;
	}
	return (0);
}*/
