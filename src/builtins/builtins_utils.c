/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:06:28 by gougier           #+#    #+#             */
/*   Updated: 2025/03/06 17:38:02 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_minishell *minishell)
{
	char		*curr_dir;
	char		*oldpwd;

	curr_dir = getcwd(NULL, 0);
	if (curr_dir == NULL)
		free_all_exit(minishell, "malloc");
	oldpwd = ft_strjoin("OLDPWD=", curr_dir);
	if (oldpwd == NULL)
		free_all_exit(minishell, "malloc");
	final_export(minishell, oldpwd);
	free(oldpwd);
	free(curr_dir);
}

char	*get_home(t_minishell *minishell, int init)
{
	char		*home;
	t_env		*tmp;

	if (minishell->default_param == 1 && init == 1)
		return (NULL);
	tmp = minishell->env;
	while (tmp)
	{
		if (ft_strncmp("HOME=", tmp->data, 5) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		return (NULL);
	}
	home = ft_strdup(tmp->subst);
	if (home == NULL)
		free_all_exit(minishell, "malloc");
	return (home);
}
