/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:37:39 by gougier           #+#    #+#             */
/*   Updated: 2025/03/06 11:16:17 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_array(char **array)
{
	int	i;

	if (array == NULL || array[0] == NULL)
		return (NULL);
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
	return (NULL);
}

t_env	*free_list_env(t_env *lst, int dup)
{
	t_env	*temp;

	while (lst)
	{
		temp = lst->next;
		free_node(lst, dup);
		lst = temp;
	}
	return (NULL);
}

void	free_list_cmd(t_list_cmd *head)
{
	t_list_cmd	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->cmd);
		free_array(temp->arg);
		free(temp);
	}
}

void	free_all_exit(t_minishell *minishell, char *str)
{
	if (str)
		perror(str);
	free_list_env(minishell->env, 1);
	if (minishell->default_home != NULL)
		free(minishell->default_home);
	free_list_env(minishell->assign_tab, 1);
	close_fd_temp(minishell);
	unlink(".heredoc");
	full_free_parsing(minishell->list_cmd);
	rl_clear_history();
	exit(minishell->exit_code);
}

int	is_a_dir(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}
