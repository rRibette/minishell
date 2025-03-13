/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:39:05 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 14:15:09 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	init_stdtemp(t_minishell *minishell);

char	*get_pwd(t_minishell *minishell)
{
	char		*curr_dir;
	char		*pwd;

	curr_dir = getcwd(NULL, 0);
	if (curr_dir == NULL)
		free_all_exit(minishell, "malloc");
	pwd = ft_strjoin("PWD=", curr_dir);
	if (pwd == NULL)
		free_all_exit(minishell, "malloc");
	free(curr_dir);
	return (pwd);
}

void	init_all(t_minishell *minishell, char **envp)
{
	minishell->list_cmd = NULL;
	minishell->env = NULL;
	minishell->exit_code = 0;
	minishell->flag_no_path = 0;
	minishell->default_home = NULL;
	minishell->default_param = 0;
	minishell->shlvl = 2;
	minishell->assign_tab = NULL;
	minishell->flag_for_export = 0;
	minishell->env = create_env(minishell, envp);
	if (!minishell->env)
		exit(2);
	minishell->default_home = get_home(minishell, 1);
}

void	init_stdtemp(t_minishell *minishell)
{
	minishell->stdin_temp = dup(STDIN_FILENO);
	if (minishell->stdin_temp == -1)
	{
		perror("dup stdin");
		exit(1);
	}
	minishell->stdout_temp = dup(STDOUT_FILENO);
	if (minishell->stdout_temp == -1)
	{
		perror("dup stdout");
		close(minishell->stdin_temp);
		exit(1);
	}
	minishell->flag_redir_out = 0;
	minishell->flag_redir_in = 0;
}
