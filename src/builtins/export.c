/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gougier <gougier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:43:23 by gougier           #+#    #+#             */
/*   Updated: 2025/02/27 14:14:37 by gougier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	alphabetic_sort(char **array)
{
	int		i;
	int		j;
	int		n;
	char	*temp;

	i = 0;
	n = 0;
	while (array[n])
		n++;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_line(char *str)
{
	int	i;

	i = 0;
	printf("export ");
	while (str[i] && str[i] != '=')
		printf("%c", str[i++]);
	if (str == NULL)
		return ;
	if (str[i] == '\0')
	{
		printf("\n");
		return ;
	}
	printf("=");
	printf("\"");
	i += 1;
	while (str[i])
		printf("%c", str[i++]);
	printf("\"");
	printf("\n");
}

static void	print_export(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
	{
		if (ft_strcmp("=/usr/bin/env", array[i]) != 0)
			print_line(array[i]);
		i++;
	}
}

static void	export_no_arg(t_minishell *minishell)
{
	char	**array;

	array = put_list_to_array(minishell->env);
	alphabetic_sort(array);
	print_export(array);
	free(array);
}

void	ft_export(t_minishell *minishell, t_list_cmd *curr_node)
{
	if (curr_node->nb_arg == 0)
		export_no_arg(minishell);
	else
		export_with_arg(minishell, curr_node);
}
