/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/07/24 12:34:41 by mabaghda         ###   ########.fr       */
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
	while ((line = readline("minishell$ ")) != NULL)
	{
		if (*line)
			add_history(line);
		start_quotes(line, &split);
		// split = ft_split(line);
		validation(split, &stack);
		init_tokens_type(&stack);
		// quotes_check(stack, &info);
		free_stack(&stack);
	}
	return (0);
}
