/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:30:53 by gougier           #+#    #+#             */
/*   Updated: 2025/03/11 11:51:27 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_newline(int sig)
{
	(void)sig;
	write (STDOUT_FILENO, "\n", 1);
}

void	signal_handler_after_rl(void)
{
	struct sigaction	sa;

	handle_ctrl_bcksl();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &display_newline;
	sigaction(SIGINT, &sa, NULL);
}

static void	sigchld_handler(int sig)
{
	pid_t	pid;

	(void)sig;
	pid = waitpid(-1, NULL, WNOHANG);
	while (pid > 0)
		pid = waitpid(-1, NULL, WNOHANG);
}

void	setup_sigchld_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigchld_handler;
	sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
}

void	signal_in_parent(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	handle_ctrl_bcksl();
}
