/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:43:49 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 11:22:41 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_temp(t_minishell *minishell)
{
	if (minishell->stdin_temp != -1)
		close(minishell->stdin_temp);
	minishell->stdin_temp = -1;
	if (minishell->stdout_temp != -1)
		close(minishell->stdout_temp);
	minishell->stdout_temp = -1;
}

int	free_and_quit_error(char *line, int fd_temp)
{
	free(line);
	close (fd_temp);
	return (-2);
}
