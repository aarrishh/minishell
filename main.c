/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/08/08 14:15:09 by arina            ###   ########.fr       */
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
	// t_env	*list_expo/rt;

	(void)argc,
	(void)argv;

	stack = NULL;
	split = NULL;
	list_env = add_env_to_list(env);
	// list_export = 
	while (1)
	{
		line = readline(P "🌸 " PB "minishell" R " " W "✦" R " ");
		if (*line)
			add_history(line);
		if (line[0] == '\0')
			continue;;
		start_quotes(line, &split);
		if (split)
			validation(split, &stack);
		init_tokens_type(&stack);
		built_in_functions(&stack, &list_env);
		free_stack(&stack);
	}
	return (0);
}
