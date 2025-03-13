/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:25:26 by rribette          #+#    #+#             */
/*   Updated: 2025/03/08 14:39:37 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list_cmd	*return_free_parsing(t_list_cmd *parsing)
{
	t_list_cmd	*tmp;

	free_redir(parsing->redir_list, 1);
	while (parsing)
	{
		tmp = parsing;
		parsing = parsing->next;
		if (tmp->arg)
			free(tmp->arg);
		free(tmp);
	}
	return (NULL);
}

void	free_redir(t_redir *redir_list, int name_keep)
{
	t_redir	*tmp;

	while (redir_list)
	{
		tmp = redir_list;
		redir_list = redir_list->next;
		if (!name_keep)
			free(tmp->filename);
		free(tmp);
	}
}

void	full_free_parsing(t_list_cmd *parsing)
{
	t_list_cmd	*tmp;

	if (!parsing)
		return ;
	if (parsing->input)
		free(parsing->input);
	while (parsing)
	{
		tmp = parsing;
		parsing = parsing->next;
		if (tmp->heredoc_file)
		{
			unlink(tmp->heredoc_file);
			free(tmp->heredoc_file);
		}
		free_chartab(tmp->arg);
		free_redir(tmp->redir_list, 0);
		free(tmp);
	}
}

void	error_full_exit(t_list_cmd *parsing, int err_code)
{
	full_free_parsing(parsing);
	exit(err_code);
}
