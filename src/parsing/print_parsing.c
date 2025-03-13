/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rribette <rribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:15:11 by rribette          #+#    #+#             */
/*   Updated: 2025/02/13 15:58:53 by rribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_list_cmd(t_list_cmd *parsing)
{
	t_list_cmd	*tmp;

	tmp = parsing;
	printf("==================================================\n");
	while (tmp)
	{
		print_list_cmd_node(tmp);
		printf("==================================================\n");
		tmp = tmp->next;
	}
}

void	print_list_cmd_node(t_list_cmd *parsing)
{
	printf("input : %s\n", parsing->input);
	print_chartab(parsing->arg);
	printf("cmd : %s\n", parsing->cmd);
	printf("nb_arg : %d\n", parsing->nb_arg);
	printf("index : %d\n", parsing->index);
	printf("size_list : %d\n", parsing->size_lst);
	print_redir_list(parsing->redir_list);
}

void	print_chartab(char **tab)
{
	int	i;

	i = 0;
	printf("cmdargs : \n");
	if (!tab)
		return ;
	while (tab[i])
	{
		printf("\t%s\n", tab[i]);
		i++;
	}
}

void	print_redir_list(t_redir *redir_list)
{
	t_redir	*tmp;

	tmp = redir_list;
	printf("redir_list : \n");
	while (tmp)
	{
		printf("\tfile : %s, quoted : %d,  mode : ", tmp->filename, tmp->quoted);
		print_redir_mode(tmp->filemode);
		tmp = tmp->next;
	}
}

void	print_redir_mode(int filemode)
{
	if (filemode == 0)
		printf("HERE_DOC\n");
	if (filemode == 1)
		printf("INREDIR\n");
	if (filemode == 2)
		printf("APPEND\n");
	if (filemode == 3)
		printf("OUTREDIR\n");
}
