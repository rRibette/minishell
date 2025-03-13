/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:32:40 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 11:23:36 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_flag = 0;

static void	launch_minishell(t_minishell *minishell)
{
	char				*line;

	while (1)
	{
		init_stdtemp(minishell);
		signal_handler();
		setup_sigchld_handler();
		line = readline("Minishell > ");
		check_signal(minishell);
		if (!line)
		{
			if (g_signal_flag == 1)
				minishell->exit_code = 130;
			write (STDOUT_FILENO, "Exit\n", 5);
			break ;
		}
		signal_handler_after_rl();
		add_history(line);
		minishell->list_cmd = parse(line, minishell);
		exec(minishell);
		full_free_parsing(minishell->list_cmd);
		minishell->list_cmd = NULL;
		close_fd_temp(minishell);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minishell			minishell;

	(void)av;
	(void)ac;
	init_all(&minishell, envp);
	launch_minishell(&minishell);
	rl_clear_history();
	free_all_exit(&minishell, NULL);
}
