/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varsubst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:56:56 by rribette          #+#    #+#             */
/*   Updated: 2025/03/06 13:30:21 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*replace_dollar(char *line, int i, t_minishell *minishell)
{
	char	*word;
	char	*newline;
	int		len;

	len = dollar_type(line + i);
	word = NULL;
	newline = NULL;
	if (len >= 0)
	{
		word = get_var(minishell, line, len - 1, i + 1);
		newline = create_newline(line, word, len, i);
	}
	else
		newline = create_special_dollar(line, i, len, minishell);
	if (word)
		free(word);
	return (newline);
}

char	*create_newline(char *line, char *var, int wordlen, int idx)
{
	char	*newline;
	int		totlen;
	int		varlen;
	int		i;

	varlen = ft_strlen(var);
	totlen = ft_strlen(line) - wordlen + varlen;
	newline = malloc((totlen + 1) * sizeof(char));
	if (!newline)
		return (NULL);
	i = 0;
	while (i < totlen)
	{
		if (i < idx)
			newline[i] = line[i];
		else if (i < idx + varlen)
			newline[i] = var[i - idx];
		else
			newline[i] = line[i - varlen + wordlen];
		i++;
	}
	newline[i] = 0;
	return (newline);
}

char	*get_var(t_minishell *minishell, char *line, int len, int idx)
{
	char	*var;

	var = ft_strldup(line + idx, len);
	if (!var)
		return (NULL);
	if (minishell->default_param && ft_strncmp(var, "PATH", 4) == 0)
	{
		free(var);
		return (ft_strdup(DEFAULT_PATH));
	}
	return (search_var(minishell, var));
}

char	*search_var(t_minishell *minishell, char *var)
{
	t_env	*env;

	env = minishell->env;
	while (env)
	{
		if (!ft_strcmp(var, env->var))
		{
			free(var);
			return (ft_strdup(env->subst));
		}
		env = env->next;
	}
	env = minishell->assign_tab;
	while (env)
	{
		if (!ft_strcmp(var, env->var))
		{
			free(var);
			return (ft_strdup(env->subst));
		}
		env = env->next;
	}
	free(var);
	return (NULL);
}
