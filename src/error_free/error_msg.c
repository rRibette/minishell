/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:29:56 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 13:47:07 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_msg(t_minishell *minishell, char *str)
{
	if (strchr(str, '/'))
	{
		if (is_a_dir(str))
		{
			join_cmd_error_msg(minishell, str, ": Is a directory\n");
			minishell->exit_code = 126;
		}	
		else
		{
			join_cmd_error_msg(minishell, str, ": No such file or directory\n");
			minishell->exit_code = 127;
		}
	}
	else
	{
		join_cmd_error_msg(minishell, str, ": command not found\n");
		minishell->exit_code = 127;
	}
}

void	exit_error_msg(char *str)
{
	write(STDERR_FILENO, "exit: ", 7);
	write(STDERR_FILENO, str, ft_strlen(str));
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

void	cd_error_msg(char *str)
{
	if (str == NULL)
		ft_putendl_fd("cd: too many arguments ", STDERR_FILENO);
	if (file_exist(str))
	{
		if (str != NULL && !is_a_dir(str))
		{
			write(STDERR_FILENO, "cd: ", 5);
			write(STDERR_FILENO, str, ft_strlen(str));
			ft_putendl_fd(": Not a directory", STDERR_FILENO);
		}	
	}
	else if (str != NULL)
	{
		write(STDERR_FILENO, "cd: ", 5);
		write(STDERR_FILENO, str, ft_strlen(str));
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
}

void	export_error_msg(char *str, t_minishell *minishell)
{
	write(STDERR_FILENO, "export: `", 10);
	join_cmd_error_msg(minishell, str, "': not a valid identifier\n");
}
