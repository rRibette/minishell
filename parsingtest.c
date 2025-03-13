/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingtest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:48:40 by rribette          #+#    #+#             */
/*   Updated: 2025/02/26 15:25:53 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "parsing.h"
#include "minishell.h"
#include "libft.h"

volatile sig_atomic_t	g_signal_flag = 0;

int	main(int argc, char *argv[], char **envp)
{
	char		*line;
	t_minishell	minishell;
	t_list_cmd	*parsing;

	(void)argc;
	(void)argv;
	init_all(&minishell, envp);
	line = readline("Test : ");
	while (line)
	{
		parsing = parse(line, &minishell);
		print_list_cmd(parsing);
		full_free_parsing(parsing);
		line = readline("Test : ");
	}
	return (1);
}
