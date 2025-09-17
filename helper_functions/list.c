/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:18:44 by arina             #+#    #+#             */
/*   Updated: 2025/09/18 00:27:49 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_token	*create_node(char **res)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	new_node->string = ft_strdup(*res);
	free(*res);
	new_node->type = 0;
	new_node->quote = 0;
	new_node->next = NULL;
	return (new_node);
}
