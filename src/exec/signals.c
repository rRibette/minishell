/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:08:09 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 11:22:57 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_ctrl_bcksl(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	new_prompt(int sig)
{
	(void)sig;
	g_signal_flag = 1;
	write (STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(void)
{
	struct sigaction	sa;

	handle_ctrl_bcksl();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &new_prompt;
	sigaction(SIGINT, &sa, NULL);
}

void	check_signal(t_minishell *minishell)
{
	if (g_signal_flag == 1)
	{
		minishell->exit_code = 130;
		g_signal_flag = 0;
	}
}

void	routine_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal_flag = 2;
		write (STDOUT_FILENO, "\n", 1);
		close (STDIN_FILENO);
	}
}
