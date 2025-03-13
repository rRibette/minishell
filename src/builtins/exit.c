/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:05:53 by gougier           #+#    #+#             */
/*   Updated: 2025/03/13 13:19:22 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_digit(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (*s == '-' || *s == '+')
	{
		flag = 1;
		i++;
	}
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		flag = 0;
		i++;
	}
	if (flag == 1 && s[i] == '\0')
		return (0);
	return (1);
}

static int	check_long_overflow(char *str)
{
	int		i;
	char	*s;

	s = "9223372036854775807";
	i = 0;
	if (ft_strlen(str) > 19)
		return (1);
	if (ft_strlen(str) < 19)
		return (0);
	if (ft_strlen(str) == 19)
	{
		while (str[i])
		{
			if (str[i] > s[i])
				return (1);
			i++;
		}
	}
	return (0);
}

static void	exit_one_arg(t_minishell *minishell, t_list_cmd *curr_node)
{
	if (check_digit(curr_node->arg[1])
		&& !check_long_overflow(curr_node->arg[1])
		&& ft_atol(curr_node->arg[1]) > 255)
				minishell->exit_code = ft_atol(curr_node->arg[1]) % 256;
	else if (check_digit(curr_node->arg[1])
		&& !check_long_overflow(curr_node->arg[1]))
		minishell->exit_code = ft_atoi(curr_node->arg[1]);
	else if (check_digit(curr_node->arg[1])
		&& check_long_overflow(curr_node->arg[1]))
	{
		exit_error_msg(curr_node->arg[1]);
		minishell->exit_code = 2;
	}		
}

void	ft_exit(t_minishell *minishell, t_list_cmd *curr_node)
{
	ft_putendl_fd("exit", 2);
	if (curr_node->nb_arg == 0)
		free_all_exit(minishell, NULL);
	if (check_digit(curr_node->arg[1]) == 0)
	{
		exit_error_msg(curr_node->arg[1]);
		minishell->exit_code = 2;
		free_all_exit(minishell, NULL);
	}
	if (curr_node->nb_arg > 1)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		minishell->exit_code = 1;
		return ;
	}
	exit_one_arg(minishell, curr_node);
	free_all_exit(minishell, NULL);
}
