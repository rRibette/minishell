/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:48:41 by rribette          #+#    #+#             */
/*   Updated: 2025/03/13 13:39:02 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_redirtoken(t_token *token)
{
	if (!token)
		return (0);
	if (token->id == HERE_DOC || token->id == INREDIR)
		return (1);
	if (token->id == OUTREDIR || token->id == APPEND)
		return (1);
	return (0);
}

char	*ft_strldup(const char *str, int size)
{
	int		len;
	char	*res;
	int		i;

	if (size < 0)
		size = 0;
	len = ft_strlen(str);
	if (len > size)
		len = size;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

int	is_redir_or_file(t_token *token)
{
	if (!token)
		return (0);
	if (is_redirtoken(token))
		return (1);
	if (token->id == FILENAME || token->id == QUOTED_FILENAME)
		return (1);
	return (0);
}
