/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/07/25 11:52:46 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_stack(t_token **stack)
{
	t_token	*tmp;

	tmp = *stack;
	while (tmp)
	{
		tmp = tmp->next;
		free(*stack);
		*stack = tmp;
	}
}

int	main(void)
{
	char	*line;
	char	**split;
	t_token	*stack;

	stack = NULL;
	split = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		start_quotes(line, &split);
		if (split)
			validation(split, &stack);
		init_tokens_type(&stack);
		free_stack(&stack);
	}
	return (0);
}
