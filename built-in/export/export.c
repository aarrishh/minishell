/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:50:14 by arina             #+#    #+#             */
/*   Updated: 2025/09/04 19:32:31 by mabaghda         ###   ########.fr       */
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

void	export_command(t_data *data)
{
	t_env	*node;

	node = NULL;
	if (data->stack->next == NULL)
	{
		print_export(data->env);
		return ;
	}
	while (data->stack->next)
	{
		data->stack = data->stack->next;
		if (check_key(data->stack->string) == -2)
			print_error_export(data->stack->string);
		if (find_equal_for_export(data->stack->string) >= 0)
			we_find_only_equal_in_string(data->stack->string, &data->env,
				&node);
		else if (find_equal_for_export(data->stack->string) == -2)
			we_find_equal_and_plus_in_string(data->stack->string, &data->env,
				&node);
		else
		{
			if (check_sameness(data->stack->string, data->env) == 0)
				node = new_node(ft_strdup(data->stack->string), ft_strdup(""));
		}
		if (node)
			env_add_back(node, &data->env);
	}
	update_envp(data);
}

void	update_envp(t_data *data)
{
	t_env	*tmp;
	char	**tmp_env;
	int		len;
	int		i;
	char	*key;

	if (!data)
		return ;
	len = 0;
	tmp = data->env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	tmp_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tmp_env)
		return ;
	tmp = data->env;
	i = 0;
	while (tmp)
	{
		if (!tmp->key || !tmp->value)
		{
			tmp->key = ft_strdup("");
			tmp->value = ft_strdup("");
		}
		key = ft_strjoin(tmp->key, "=");
		if (!key)
			key = ft_strdup("");
		tmp_env[i] = ft_strjoin(key, tmp->value);
		free(key);
		if (!tmp_env[i])
		{
			tmp_env[i] = NULL;
			free_array(tmp_env);
			return ;
		}
		i++;
		tmp = tmp->next;
	}
	tmp_env[i] = NULL;
	if (data->env_arr)
		free_array(data->env_arr);
	data->env_arr = tmp_env;
}
