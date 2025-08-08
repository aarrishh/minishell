/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:50:14 by arina             #+#    #+#             */
/*   Updated: 2025/08/08 19:08:47 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	we_find_only_equal_in_string(char *str, t_env **env, t_env **node)
{
	if (check_sameness(str, *env) == 0)
	{
		if ((check_key(ft_substr(str, 0, find_equal(str))) == -1) \
			|| (check_key(ft_substr(str, 0, find_equal(str))) == -2))
			(*node) = NULL;
		else
		{
			(*node) = new_node(ft_substr(str, 0, find_equal(str)), \
			ft_strdup(ft_strchr(str, '=') + 1));
			check_i_have_value_after_equal_symbol(find_equal(str), str, node);
		}
	}
	else
	{
		change_value(str, env);
		check_i_have_value_after_equal_symbol_version_two(find_equal(str), str, env);
	}
}

void	we_find_equal_and_plus_in_string(char *str, t_env **env, t_env **node)
{
	if (check_sameness(str, *env) == 2)
		change_value_for_plus_equal_case(str, env);
	else
		(*node) = new_node(ft_substr(str, 0, find_plus(str)), \
		ft_strdup(ft_strchr(str, '=') + 1));
}

void	export_command(t_token *stack, t_env **env)
{
	t_env	*node;

	node = NULL;
	if (stack->next == NULL)
	{
		print_export(*env);
		return ;
	}
	while (stack->next)
	{
		stack = stack->next;
		if (check_key(stack->string) == -2)
			print_error_export(stack->string);
		if (find_equal_for_export(stack->string) >= 0)
			we_find_only_equal_in_string(stack->string, env, &node);
		else if (find_equal_for_export(stack->string) == -2)
			we_find_equal_and_plus_in_string(stack->string, env, &node);
		else
		{
			if (check_sameness(stack->string, *env) == 0)
				node = new_node(stack->string, ft_strdup(""));
		}
		if (node)
			env_add_back(node, env);
	}
}
