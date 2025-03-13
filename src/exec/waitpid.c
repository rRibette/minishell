/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:00:50 by gougier           #+#    #+#             */
/*   Updated: 2025/03/04 13:37:42 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_dfl(void)
{
	struct sigaction	sa_ign;

	ft_memset(&sa_ign, 0, sizeof(sa_ign));
	sa_ign.sa_handler = SIG_DFL;
	sigaction(SIGCHLD, &sa_ign, NULL);
}

static void	write_and_update(t_minishell *minishell, int flag)
{
	if (flag == 1)
	{
		write (STDOUT_FILENO, "\n", 1);
		minishell->exit_code = 130;
	}
	else if (flag == 2)
	{
		write (1, "Quit (core dumped)\n", 20);
		minishell->exit_code = 131;
	}
}

static int	final_loop(int len, pid_t *array_pid,
			t_minishell *minishell, int flag)
{
	int		i;
	pid_t	pid;
	int		status;

	status = 0;
	i = 0;
	while (i < len)
	{
		pid = waitpid(array_pid[i], &status, 0);
		if (WIFEXITED(status))
			minishell->exit_code = WEXITSTATUS(status);
		if (WTERMSIG(status) == SIGINT)
		{
			minishell->exit_code = 130;
			flag = 1;
		}
		i++;
	}
	if (WTERMSIG(status) == SIGQUIT)
		write_and_update(minishell, 2);
	return (flag);
}

void	waitpid_loop(t_minishell *minishell, pid_t *array_pid)
{
	int					len;
	int					flag;
	int					status;
	struct sigaction	sa_old;

	sigaction(SIGCHLD, NULL, &sa_old);
	signal_dfl();
	flag = 0;
	status = 0;
	len = minishell->list_cmd->size_lst;
	flag = final_loop(len, array_pid, minishell, flag);
	if (flag)
		write_and_update(minishell, 1);
	sigaction(SIGCHLD, &sa_old, NULL);
}
