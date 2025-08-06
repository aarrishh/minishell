/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/08/06 11:25:01 by mabaghda         ###   ########.fr       */
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

	(void)argc, (void)argv;
	stack = NULL;
	split = NULL;
	env_struct = NULL;
	(void)argc;
	(void)argv;
	env_struct = add_env_to_list(env);
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		if (line[0] == '\0')
			continue ;
		if (!start_quotes(line, &split, &env_struct))
			continue ;
		if (split)
			validation(split, &stack);
		env_struct = add_env_to_list(env);
		init_tokens_type(&stack);
		built_in_functions(&stack, &env_struct);
		free_stack(&stack);
	}
	return (0);
}
