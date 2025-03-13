/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:08:54 by gougier           #+#    #+#             */
/*   Updated: 2025/03/06 13:21:11 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void cd_dot_dot(t_minishell *minishell)
// {
// 	t_list_cmd	*curr_node;
// 	int			i;
// 	char		*curr_dir;
// 	char		*new_dir;

// 	curr_node = minishell->list_cmd;
// 	i = 0;
// 	curr_dir = getcwd(NULL, 0);
// 	if (curr_dir == NULL)
// 		free_all_exit(minishell, "malloc");
// 	while (curr_dir[i])
// 		i++;
// 	while (curr_dir[i] != '/')
// 		i--;
// 	new_dir = ft_strndup(curr_dir, i);
// 	if (new_dir == NULL)
// 		free_all_exit(minishell, "malloc");
// 	chdir(new_dir);
// 	free(curr_dir);
// 	free(new_dir);
// }

static void	cd_home(t_minishell *minishell)
{
	char	*home;

	home = minishell->default_home;
	if (home == NULL)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		return ;
	}	
	chdir(home);
}

static void	cd_default_home(t_minishell *minishell)
{
	char	*home;

	home = minishell->default_home;
	chdir(home);
}

static int	check_arg(t_list_cmd *curr_node)
{
	if (ft_strncmp("..", curr_node->arg[1], 2) == 0)
		return (1);
	else if (ft_strncmp("~", curr_node->arg[1], 1) == 0)
		return (2);
	return (0);
}

static void	cd_one_arg(t_minishell *minishell, t_list_cmd *curr_node)
{
	if (check_arg(curr_node) == 1)
	{
		update_oldpwd(minishell);
		chdir(".");
	}
	if (check_arg(curr_node) == 2)
	{
		update_oldpwd(minishell);
		cd_default_home(minishell);
	}
	else
	{
		update_oldpwd(minishell);
		if (chdir(curr_node->arg[1]) != 0)
		{
			cd_error_msg(curr_node->arg[1]);
			minishell->exit_code = 1;
		}
	}
}

void	ft_cd(t_minishell *minishell, t_list_cmd *curr_node)
{
	if (curr_node->nb_arg > 1)
	{
		cd_error_msg(NULL);
		minishell->exit_code = 1;
	}
	if (curr_node->nb_arg == 0)
	{
		update_oldpwd(minishell);
		cd_home(minishell);
	}
	if (curr_node->nb_arg == 1)
		cd_one_arg(minishell, curr_node);
}
