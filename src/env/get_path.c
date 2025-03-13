/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:48:38 by gougier           #+#    #+#             */
/*   Updated: 2025/02/24 16:47:07 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* int	alloc_array_env(char **envp, t_env *env)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	env->array = malloc(sizeof(char *) * (i + 1));
	if (env->array == NULL)
		return (ERROR);
	return (SUCCESS);
} */

char	**get_paths(char **envp)
{
	int		i;
	char	**path;

	path = NULL;
	i = 0;
	if (!envp || !envp[0])
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			path = ft_split(envp[i] + 5, ':');
		i++;
	}
	return (path);
}

char	**path_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, "PATH"))
			return (ft_split(tmp->subst, ':'));
		tmp = tmp->next;
	}
	return (NULL);
}
