/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:38:45 by gougier           #+#    #+#             */
/*   Updated: 2025/02/20 13:30:36 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_nlarg_echo(char *arg);

void	ft_echo(t_minishell *minishell, t_list_cmd *curr_node)
{
	int		i;
	int		nlarg;
	char	**arg;

	arg = curr_node->arg;
	i = 1;
	nlarg = 0;
	while (is_nlarg_echo(arg[i]))
	{
		nlarg = 1;
		i++;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (i < curr_node->nb_arg)
			write(1, " ", 1);
		i++;
	}
	if (!nlarg)
		write(1, "\n", 1);
	minishell->exit_code = 0;
}

static int	is_nlarg_echo(char *arg)
{
	int	i;

	i = 1;
	if (!arg || arg[0] != '-')
		return (0);
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i])
		return (0);
	return (1);
}
