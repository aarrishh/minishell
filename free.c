/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:36:41 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/11 19:46:28 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (*env)
	{
		while (*env)
		{
			tmp = tmp->next;
			free((*env)->key);
			free((*env)->value);
			free((*env));
			*env = tmp;
		}
	}
}

void	free_stack(t_token **stack)
{
	t_token	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		if ((*stack)->string)
			free((*stack)->string);
		free(*stack);
		*stack = tmp;
	}
}

void	free_all(t_env **env, t_token **stack, char **split)
{
	if (env && *env)
	{
		free_env(env);
		*env = NULL;
	}
	if (stack && *stack)
	{
		free_stack(stack);
		*stack = NULL;
	}
	if (split)
	{
		free_array(split);
		split = NULL;
	}
}
