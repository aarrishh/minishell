/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/08/01 13:53:14 by arimanuk         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	**split;
	t_token	*stack;
	t_env	*list_env;

	(void)argc,
	(void)argv;

	stack = NULL;
	split = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		if (line[0] == '\0')
			continue;;
		start_quotes(line, &split);
		if (split)
			validation(split, &stack);
		list_env = add_env_to_list(env);
		init_tokens_type(&stack);
		built_in_functions(&stack, &list_env);
		free_stack(&stack);
	}
	return (0);
}
