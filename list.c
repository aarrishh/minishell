/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:18:44 by arina             #+#    #+#             */
/*   Updated: 2025/07/28 19:14:58 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_token *node, t_token **a)
{
	t_token	*tmp;

	if (*a == NULL)
	{
		*a = node;
		return ;
	}
	tmp = *a;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}

t_token	*create_node(char *res)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	new_node->string = res;
	new_node->type = 0;
	new_node->next = NULL;
	// printf("res = %s\n", res);
	return (new_node);
}

// int	check_n_count(char *str)
// {
// 	int	i;

// 	i = 2;
// 	if (ft_strlen(str) > 2)
// 	{
// 		while (str[i])
// 		{
// 			if (str[i] == 'n')
// 				i++;
// 			else
// 				return (-1);
// 		}	
// 	}
// 	return (0);
// }

// void	*echo_command(t_token **stack)
// {
// 	t_token *tmp;
// 	int	flag;

// 	flag = 0;
// 	if (!(*stack)->next)
// 		return(printf("\n"), "");
// 	tmp = (*stack)->next;
// 	while (tmp && ft_strncmp(tmp->string, "-n", 2) == 0)
// 	{
// 		flag = 1;
// 		if (check_n_count(tmp->string) == -1)
// 			flag = 0;
// 		tmp = tmp->next;
// 	}
// 	while (tmp && tmp->next)
// 	{
// 		printf("%s ", tmp->string);
// 		tmp = tmp->next;
// 	}
// 	if (flag == 1)
// 		printf("%s", tmp->string);
// 	else
// 		printf("%s\n", tmp->string);
// 	return ("");
// }