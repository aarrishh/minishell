/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/07/21 17:18:26 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	char	**split;
	t_token	*stack;
	t_info	info;

	stack = NULL;
	while ((line = readline("minishell$ ")) != NULL)
	{
		if (*line)
			add_history(line);
		split = ft_split(line);
		validation(split, &stack);
		init_info(&info);
		quotes_check(stack, &info);
		// prinit_matrix(split);
		free_stack(&stack);
	}
	return (0);
}
