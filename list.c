/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:18:44 by arina             #+#    #+#             */
/*   Updated: 2025/07/19 19:49:10 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_stack *node, t_stack **a)
{
	t_stack	*tmp;

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

t_stack	*create_node(char *res)
{
	t_stack	*new_node;

	new_node = malloc(sizeof(t_stack));
	new_node->string = res;
	new_node->next = NULL;
	// printf("res = %s\n", res);
	return (new_node);
}
