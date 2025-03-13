/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:00:46 by gougier           #+#    #+#             */
/*   Updated: 2025/02/26 11:21:27 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_character(char *str, char character)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == character)
			return (1);
		i++;
	}
	return (0);
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
	{
		printf("array[%d] = '%s'\n", i, array[i]);
		i++;
	}
}

void	print_list_env(t_env *list)
{
	int			i;
	t_env		*current;

	i = 0;
	current = list;
	while (current)
	{
		if (find_character(current->data, '='))
		{
			write(STDOUT_FILENO, current->data, ft_strlen(current->data));
			write(STDOUT_FILENO, "\n", 1);
		}
		current = current->next;
		i++;
	}
}
