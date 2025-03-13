/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:35:08 by gougier           #+#    #+#             */
/*   Updated: 2024/05/28 17:00:31 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_char;
	unsigned char	*s2_char;
	size_t			i;

	i = 0;
	s1_char = (unsigned char *) s1;
	s2_char = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (i + 1 < n)
	{
		if (s1_char[i] != s2_char[i])
			return (s1_char[i] - s2_char[i]);
		i++;
	}
	return (s1_char[i] - s2_char[i]);
}
/*#include <assert.h>
#include <stdio.h>
int main(void)
{
	char str1[15];
   char str2[15];
   int ret;

   memcpy(str1, "ABCDEF", 6);
   memcpy(str2, "abcdef", 6);

   ret = memcmp(str1, str2, 5);

   if(ret > 0) {
      printf("str2 is less than str1");
   } else if(ret < 0) {
      printf("str1 is less than str2");
   } else {
      printf("str1 is equal to str2");
  }
}*/
