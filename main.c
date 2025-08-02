/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/08/02 16:00:44 by mabaghda         ###   ########.fr       */
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
	t_env	*env_struct;

	stack = NULL;
	split = NULL;
	env_struct = NULL;
	(void)argc;
	(void)argv;
	chgitem_env(env, &env_struct);
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		if (line[0] == '\0')
			continue;
		start_quotes(line, &split, &env_struct);
		if (split)
			validation(split, &stack);
		init_tokens_type(&stack);
		if (built_in_functions(&stack) == 1)
			return (1);
		free_stack(&stack);
	}
	return (0);
}
