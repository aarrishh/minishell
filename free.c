/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:36:41 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/16 22:08:08 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array || !(*array))
	{
		free(array);
		return ;
	}
	while (array[i])
	{
		if (array[i])
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
		{
			free((*stack)->string);
			(*stack)->string = NULL;
		}
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
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
