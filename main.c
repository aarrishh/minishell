/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/08/11 18:36:50 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (*env)
	{
		tmp = tmp->next;
		free((*env)->key);
		free((*env)->value);
		free((*env));
		*env = tmp;
	}
}

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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**split;
	t_token	*stack;
	t_env	*env_struct;

	(void)argc, (void)argv;
	stack = NULL;
	split = NULL;
	env_struct = add_env_to_list(envp);
	while (1)
	{
		line = readline("🌸 " PB "minishell" R " " W "✦" R " ");
		if (!line)
			break ;
		if (line)
			add_history(line);
		// if (line)
		// 	continue ;
		if (!start_quotes(line, &split, &env_struct))
			continue ;
		if (split)
			validation(split, &stack);
		init_tokens_type(&stack);
		if (stack && has_pipe(stack))
			execute_pipe(&stack, &env_struct, envp, split);
		else if (stack)
		{
			if (is_builtin_cmd(stack->string))
				built_in_functions(&stack, stack->string, &env_struct, split);
			else
				execute_else(&env_struct, split, envp);
		}
		free_stack(&stack);
		free(line);
		free_array(split);
	}
	return (0);
}
