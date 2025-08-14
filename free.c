/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:36:41 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/14 11:23:44 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

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

void	free_all(t_env **env, t_token **stack, char **split)
{
	if (env)
		free_env(env);
	if (stack)
		free_stack(stack);
	if (split)
		free(split);
}