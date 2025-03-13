/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:18:20 by gougier           #+#    #+#             */
/*   Updated: 2025/02/24 10:58:40 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_lst_cmd(t_list_cmd *lst)
{
	int				i;
	t_list_cmd		*current;

	if (lst == NULL)
		return (0);
	current = lst;
	i = 0;
	if (!current)
		return (0);
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}
