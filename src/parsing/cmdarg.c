/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdarg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:55:15 by rribette          #+#    #+#             */
/*   Updated: 2025/03/06 17:41:02 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int		cmdarg_size(char **cmdarg);
static void		fill_cmdargs(char **cmdargs, t_token *list);

t_token	*get_cmdargs(t_list_cmd *parsing, t_token *list, t_minishell *msh)
{	
	char	**cmdargs;

	if (!list || list->id != CMD)
		return (list);
	cmdargs = init_cmdargs(list);
	if (!cmdargs)
		return (NULL);
	fill_cmdargs(cmdargs, list);
	cmdargs = cmdarg_dollar(cmdargs, msh);
	parsing->arg = cmdargs;
	parsing->cmd = cmdargs[0];
	parsing->nb_arg = cmdarg_size(cmdargs);
	return (list);
}

char	**init_cmdargs(t_token *list)
{
	int		len;
	char	**res;

	len = get_nbarg(list);
	res = malloc((len + 1) * sizeof(char *));
	return (res);
}

int	get_nbarg(t_token *list)
{
	t_token	*tmp;
	int		nb;

	if (!list || list->id != CMD)
		return (0);
	tmp = list->next;
	nb = 1;
	while (tmp && (tmp->id == CMDARG || is_redir_or_file(tmp)))
	{
		if (tmp->id == CMDARG)
			nb++;
		tmp = tmp->next;
	}
	return (nb);
}

static int	cmdarg_size(char **cmdarg)
{
	int	i;

	i = 0;
	while (cmdarg[i])
		i++;
	if (i)
		return (i - 1);
	return (i);
}

static void	fill_cmdargs(char **cmdargs, t_token *list)
{
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = list->next;
	cmdargs[0] = list->str;
	while (tmp && (tmp->id == CMDARG || is_redir_or_file(tmp)))
	{
		if (tmp->id == CMDARG)
		{
			cmdargs[i] = tmp->str;
			i++;
		}
		tmp = tmp->next;
	}
	cmdargs[i] = 0;
}
