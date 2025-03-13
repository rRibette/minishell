/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdarg_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:43:01 by rribette          #+#    #+#             */
/*   Updated: 2025/03/13 10:29:03 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**cmd_del_line(char **cmdarg, int index);
static char	**insert_cmdarg(char **cmdarg, int index);

char	**cmdarg_dollar(char **cmdargs, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (cmdargs[i])
	{
		if (ft_strchr(cmdargs[i], '$'))
		{
			cmdargs = cmdarg_line(cmdargs, i, minishell);
			if (!cmdargs)
				return (NULL);
		}
		find_quotes(cmdargs[i]);
		i++;
	}
	return (cmdargs);
}

char	**cmdarg_line(char **cmdarg, int index, t_minishell *minishell)
{
	int	len;

	cmdarg[index] = find_dollar(cmdarg[index], minishell, 0);
	if (!cmdarg[index])
		return (NULL);
	len = cmdarg_cw(cmdarg[index]);
	if (!len)
		return (cmd_del_line(cmdarg, index));
	else if (len == 1)
		return (cmdarg);
	else
		return (insert_cmdarg(cmdarg, index));
}

static char	**cmd_del_line(char **cmdarg, int index)
{
	char	*line;

	line = del_line(cmdarg, index);
	free(line);
	return (cmdarg);
}

static char	**insert_cmdarg(char **cmdarg, int index)
{
	char	*line;
	char	**newtab;
	char	**tmptab;

	line = del_line(cmdarg, index);
	tmptab = cmdargs_split(line);
	if (!tmptab)
		return (NULL);
	newtab = chartab_merge(cmdarg, tmptab, index);
	free(cmdarg);
	free(line);
	free(tmptab);
	return (newtab);
}
