/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:50:14 by arina             #+#    #+#             */
/*   Updated: 2025/09/14 18:18:32 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	we_find_only_equal_in_string(char *str, t_env **env, t_env **node)
{
	char	*sub;

	if (check_sameness(str, *env) == 0)
	{
		sub = ft_substr(str, 0, find_equal(str));
		if ((check_key(sub) == -1) || (check_key(sub) == -2))
			(*node) = NULL;
		else
		{
			(*node) = new_node(sub, ft_strdup(ft_strchr(str, '=') + 1));
			check_i_have_value_after_equal_symbol(find_equal(str), str, node);
			return ;
		}
		free(sub);
	}
	else
	{
		change_value(str, env);
		check_i_have_value_after_equal_symbol_version_two(find_equal(str), str,
			env);
	}
}

void	we_find_equal_and_plus_in_string(char *str, t_env **env, t_env **node)
{
	if (check_sameness(str, *env) == 2)
		change_value_for_plus_equal_case(str, env);
	else
		(*node) = new_node(ft_substr(str, 0, find_plus(str)),
				ft_strdup(ft_strchr(str, '=') + 1));
}

void	handle_export_token(t_token *token, t_env **env)
{
	t_env	*node;

	node = NULL;
	if (check_key(token->string) == -2)
	{
		print_error_export(token->string);
		return ;
	}
	if (find_equal_for_export(token->string) >= 0)
		we_find_only_equal_in_string(token->string, env, &node);
	else if (find_equal_for_export(token->string) == -2)
		we_find_equal_and_plus_in_string(token->string, env, &node);
	else
	{
		if (check_sameness(token->string, *env) == 0)
			node = new_node(ft_strdup(token->string), ft_strdup(""));
	}
	if (node)
	{
		env_add_back(node, env);
		node = NULL;
	}
}

void	*export_command(t_data *data, t_token *stack)
{
	if (stack->next == NULL || stack->next->type != WORD)
		return (print_export(data->env), NULL);
	stack = stack->next;
	while (stack && stack->type == WORD)
	{
		handle_export_token(stack, &data->env);
		stack = stack->next;
	}
	return (NULL);
}
