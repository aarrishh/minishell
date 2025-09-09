/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:35:34 by arina             #+#    #+#             */
/*   Updated: 2025/09/09 18:09:42 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_error_export(char *str)
{
	(void)str;
	g_exit_status = 1; // het poxel 1
	write (2, "minishell: export: `", 21);
	write (2, str, ft_strlen(str));
	write (2, "': not a valid identifier\n", 27);
	// printf("minishell: export: `%s': not a valid identifier\n", str);
}

t_env	*new_node_for_export(char *key, char *value, int flag)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->key = key;
	new_node->value = value;
	new_node->flag = flag;
	new_node->next = NULL;
	return (new_node);
}

t_env	*copy_env_for_print(t_env *env)
{
	t_env	*tmp = NULL;
	t_env	*cur_node;

	while (env)
	{
		cur_node = new_node_for_export(ft_strdup(env->key),
				ft_strdup(env->value), env->flag);
		env_add_back(cur_node, &tmp);
		env = env->next;
	}
	return (tmp);
}

void	free_list(t_env **copy)
{
	t_env	*tmp;

	while (*copy)
	{
		tmp = (*copy)->next;
		free((*copy)->key);
		free((*copy)->value);
		(*copy)->next = NULL;
		free(*copy);
		(*copy) = tmp;
	}
}

void	print_export(t_env *env)
{
	t_env	*tmp;
	t_env	*head;

	tmp = copy_env_for_print(env);
	head = tmp;
	sort_env(tmp);
	while (tmp)
	{
		if (ft_strcmp(tmp->value, "") == 0 && tmp->flag == 0)
			printf("declare -x %s\n", tmp->key);
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	free_list(&head);
}

