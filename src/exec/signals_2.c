/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:15:16 by gougier           #+#    #+#             */
/*   Updated: 2025/03/11 13:36:37 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	routine_child(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

static void	routine_ctrl_backsl(int signal)
{
	(void)signal;
	write (1, "Quit (core dumped)\n", 20);
}

void	sig_handler_in_child(void)
{
	struct sigaction	sa;

	sa.sa_handler = &routine_child;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = &routine_ctrl_backsl;
	sigaction(SIGQUIT, &sa, NULL);
}

void	sig_handler_in_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = &routine_heredoc;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

int	check_signal_hered(t_minishell *minishell)
{
	if (g_signal_flag == 2)
	{
		minishell->exit_code = 130;
		return (1);
	}
	return (0);
}
